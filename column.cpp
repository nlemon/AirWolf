#include<iostream>
#include"column.h"


//MISSILE METHODS
void Column::Missile::paint(XInfo& xinfo){

  XFillArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);
  XDrawArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);

}


void Column::Missile::move(XInfo& xinfo){

  x -= xinfo.scrollingSpeed;
  y -= xinfo.scrollingSpeed;

}


Column::Missile::Missile(int xval, int yval, int w, int h) : Displayable(xval, yval, w, h){}


//BLOCK METHODS
Column::Block::Block(int w, int h) : width(w), height(h){}


//HEALTORB METHODS 


void Column::HealthOrb::paint(XInfo& xinfo){

  XFillArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);
  XDrawArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);

}


void Column::HealthOrb::move(XInfo& xinfo){

  x -= xinfo.scrollingSpeed;

}


Column::HealthOrb::HealthOrb(int xval, int yval, int w, int h) : Displayable(xval, yval, w, h){}


//POINTS METHODS
void Column::Points::paint(XInfo& xinfo){

  XDrawImageString(xinfo.display, xinfo.pixie, xinfo.gc, x, y, "50", 2);
  
}


void Column::Points::move(XInfo& xinfo){

  x -= xinfo.scrollingSpeed;
  y -= xinfo.scrollingSpeed;

}


Column::Points::Points(int xval, int yval, int w, int h) : Displayable(xval, yval, w, h){}


//COLUMN METHODS
void Column::paint(XInfo& info){

  int currentHeight = y;
  if(missiles != NULL && !(missiles->empty())){

    //check to see if it's time to fire off a missile
    if(((y - blockey->height) - missiles->back()->getY()) > (info.missileFrequency * blockey->height)){

      fireMissile();

    }

    std::list<Missile*>::iterator missile = missiles->begin();

    //silo and silo tip positions
    int siloX = x + (blockey->width / 3);
    int siloY = y - (3 * (blockey->height / 4));

    int siloTipX = siloX + (blockey->width / 9);
    int siloTipY = y - blockey->height;

    //loop through and draw all missiles currently deployed
    for(int i = 0; i < missiles->size(); i++, missile++){

      (*missile)->paint(info);

    }

    //draw the silo
    XDrawRectangle(info.display, info.pixie, info.gc, siloX, siloY, blockey->width / 3, 3 * (blockey->height / 4));
    XDrawRectangle(info.display, info.pixie, info.gc, siloTipX, siloTipY, blockey->width / 9, blockey->height / 4);
 

  }

  //draw the column
  for(int i = 0; i < numberOfBlocks; i++){

    XDrawRectangle(info.display, info.pixie, info.gc, x, currentHeight, blockey->width, blockey->height);
    currentHeight += blockey->height;

  }

  if(orbo != NULL){

    //draw the orb
    orbo->paint(info);

  }

  if(killTrophy != NULL){

    killTrophy->paint(info);

  }

}


void Column::move(XInfo& xinfo){

  //move the column
  x -= xinfo.scrollingSpeed;

  if(missiles != NULL && !(missiles->empty())){

    //move the missiles
    std::list<Missile*>::iterator missile = missiles->begin();

    for(int i = 0; i < missiles->size(); i++, missile++){
      (*missile)->move(xinfo);
    }

  }

  if(orbo != NULL){

    orbo->move(xinfo);

  }

  if(killTrophy != NULL){
    killTrophy->move(xinfo);
  }

}

void Column::fireMissile(){

  Missile* smiley = new Missile(x + (4 * (blockey->width / 9)), y - (5 * (blockey->height / 4)), blockey->width / 9, blockey->height / 4);
  missiles->push_back(smiley);

}

void Column::obliterate(XInfo& xinfo, destroyable object){

  if(object == BLOCK){
    numberOfBlocks--;
    y += blockey->height;
  }

  if(object == SILO){
    delete missiles;
    missiles = NULL;
    killTrophy = new Points(x + (blockey->width / 4), y - (blockey->height / 3), blockey->width / 2, blockey->height / 3);
    xinfo.addToPointTotal();
  }

  if(object == ORB){
    delete orbo;
    orbo = NULL;
  }

}


bool Column::hasGunner(){
  if(missiles == NULL || missiles->empty()) return false;
  return true;
}


bool Column::gotHealth(Displayable& helicopter){

  //column has no health 
  if(orbo == NULL){
    return false;
  }

  int heliY1 = helicopter.getY() - (orbo->getHeight() / 4);
  int heliY2 = heliY1 + helicopter.getHeight() + (orbo->getHeight() / 4);

  int orbMidpointY = orbo->getY() + (orbo->getHeight() / 2);

  if((orbMidpointY < heliY2) && (orbMidpointY > heliY1)){
    return true;
  }
  return false;
}


bool Column::missileStrike(Displayable& helicopter){

  //column has no gunner -> column has no missiles associated with it
  if(missiles == NULL || missiles->empty()){
    return false;
  }

  int heliY1 = helicopter.getY();
  int heliY2 = heliY1 + helicopter.getHeight();

  std::list<Missile*>::iterator missile = missiles->begin();
 
  //loop through missiles and see if one has hit our hero
  for(int i = 0; i < missiles->size(); i++, missile++){

    if(((*missile)->getY() < heliY2) && ((*missile)->getY() > heliY1)){//helicopter struck by missile
      missiles->erase(missile);
      return true;
    }
  }
  return false;
}


Column::Column(int xval, XInfo& info){

  x = xval;

  //randomly generate the height of the column
  numberOfBlocks = rand() % 10;
  blockey = new Block(info.windowWidth / 15, info.windowHeight / 15);
  y = info.windowHeight - (blockey->height * numberOfBlocks);
  width = blockey->width;
  height = blockey->height;

  missiles = NULL;
  orbo = NULL;
  killTrophy = NULL;

  int isMissile = rand() % 10;
  int isHealth = rand() % 200;

  //there is a one in three chance of generating a missile silo
  if(isMissile < 4){

    missiles = new std::list<Missile*>();
    fireMissile();

  }

  if(isHealth < 10){

    orbo = new HealthOrb(x + (blockey->width / 3), y - (blockey->height * 5), blockey->width / 3, blockey->height / 2);

  }
 
}


Column::~Column(){

  delete blockey;
  if(missiles != NULL) delete missiles;
  if(orbo != NULL) delete orbo;
  if(killTrophy != NULL) delete killTrophy;

}
