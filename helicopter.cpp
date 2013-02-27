#include<iostream>
#include"helicopter.h"


//PROPELLER METHODS
void Helicopter::Propeller::paint(XInfo& xinfo){

  XFillArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);

}


void Helicopter::Propeller::move(XInfo& xinfo){

  switch(xinfo.direction){

  case DOWN:
    y += speed; break;

  case LEFT:
    x -= speed; break;

  case UP:
    y -= speed; break;

  case RIGHT:
    x += speed; break;

  }
}


Helicopter::Propeller::Propeller(int xval, int yval, int w, int h) : Displayable(xval, yval, w, h){}


//BODY METHODS
void Helicopter::Body::paint(XInfo& xinfo){

  XFillArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);

}


void Helicopter::Body::move(XInfo& xinfo){

  switch(xinfo.direction){

  case DOWN:
    y += speed; break;

  case LEFT:
    x -= speed; break;

  case UP:
    y -= speed; break;

  case RIGHT:
    x += speed; break;

  }
}


Helicopter::Body::Body(int xval, int yval, int w, int h) : Displayable(xval, yval, w, h){}


//TAIL METHODS
void Helicopter::Tail::paint(XInfo& xinfo){

  XFillArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);

}


void Helicopter::Tail::move(XInfo& xinfo){

  switch(xinfo.direction){

  case DOWN:
    y += speed; break;

  case LEFT:
    x -= speed; break;

  case UP:
    y -= speed; break;

  case RIGHT:
    x += speed; break;

  }
}


Helicopter::Tail::Tail(int xval, int yval, int w, int h) : Displayable(xval, yval, w, h){}


//BOMB METHODS
void Helicopter::Bomb::paint(XInfo& xinfo){

  //paint the bomb
  XDrawArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);

}


void Helicopter::Bomb::move(XInfo& xinfo){

  //move the bomb
  x += nukeSpeed;
  y += 3;

}


Helicopter::Bomb::Bomb(int xval, int yval, int w, int h, int s) : Displayable(xval, yval, w, h){

  nukeSpeed = s;

}


//HEALTHBAR METHODS
void Helicopter::HealthBar::paint(XInfo& xinfo){

  XDrawRectangle(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height);

  if(life > 0){
    XFillRectangle(xinfo.display, xinfo.pixie, xinfo.gc, x, y, life, height);
    return;
  }

  XFillRectangle(xinfo.display, xinfo.pixie, xinfo.gc, x, y, 0, height);
}


void Helicopter::HealthBar::move(XInfo& xinfo){}


Helicopter::HealthBar::HealthBar(int w, int h) : Displayable(20, 20, w, h){

  life = w;
  standardRefill = w / 10; 

}


//ROCKET METHODS
void Helicopter::Rocket::paint(XInfo& xinfo){

  XFillArc(xinfo.display, xinfo.pixie, xinfo.gc, x, y, width, height, 0, 360 * 64);

}


void Helicopter::Rocket::move(XInfo& xinfo){

  x += (2 * xinfo.scrollingSpeed);

}


Helicopter::Rocket::Rocket(int xval, int yval, int w, int h) : Displayable(xval, yval, w, h){}


//HELICOPTER METHODS
void Helicopter::paint(XInfo& xinfo){

  //paint the helicopter
  propster->paint(xinfo);
  theBod->paint(xinfo);
  whip->paint(xinfo);

  //piece the helicopter together
  //draw a line connecting the propeller and body
  XDrawLine(xinfo.display, xinfo.pixie, xinfo.gc, propster->getX() + (propster->getWidth() / 2), propster->getY() + propster->getHeight(), theBod->getX() + (theBod->getWidth() / 2), theBod->getY());

  //draw a line connecting the tail and body
  XDrawLine(xinfo.display, xinfo.pixie, xinfo.gc, whip->getX() + whip->getWidth(), whip->getY() + (whip->getHeight() / 2), theBod->getX(), theBod->getY() + (theBod->getHeight() / 2));

  //paint the bombs, if there are any
  if(!hellfireBrigade->empty()){

    std::list<Bomb*>::iterator firstNuke = hellfireBrigade->begin();
    std::list<Bomb*>::iterator lastNuke = hellfireBrigade->end();

    for(firstNuke; firstNuke != lastNuke; firstNuke++){

      (*firstNuke)->paint(xinfo);

    }

  }

  //paint the rockets, if there are any
  if(!(wolfpack->empty())){

    std::list<Rocket*>::iterator rocket = wolfpack->begin();

    for(int i = 0; i < wolfpack->size(); i++, rocket++){

      (*rocket)->paint(xinfo);

    }

  }

  //paint the health bar
  lifeblood->paint(xinfo);

}


void Helicopter::move(XInfo& xinfo){

  //keep track of which direction you are heading
  if(xinfo.direction == LEFT){
    movementDirection -= speed;

  }

  if(xinfo.direction == RIGHT){
    movementDirection += speed;
  }

  //move the helicopter
  propster->move(xinfo);
  theBod->move(xinfo);
  whip->move(xinfo);

  //move the bombs, if there are any
  if(!hellfireBrigade->empty()){

    std::list<Bomb*>::iterator firstNuke = hellfireBrigade->begin();
    std::list<Bomb*>::iterator lastNuke = hellfireBrigade->end();

    for(firstNuke; firstNuke != lastNuke; firstNuke++){

      (*firstNuke)->move(xinfo);

    }

    //clear the bombs that have left the screen
    if(hellfireBrigade->front()->getY() > xinfo.windowHeight){

      hellfireBrigade->pop_front();

    }
  }

  //move the rockets, if any
  if(!(wolfpack->empty())){

    std::list<Rocket*>::iterator rocket = wolfpack->begin();

    for(int i = 0; i < wolfpack->size(); i++, rocket++){

      (*rocket)->move(xinfo);

    }

    //clear the rockets that have left the screen
    if(wolfpack->front()->getX() > xinfo.windowWidth){

      wolfpack->pop_front();

    }

  }
}


void Helicopter::nuke(){

  int nukeSpeed = 0;
  if(movementDirection > 0){//moving forward, drop bomb with speed of helicopter
    nukeSpeed = speed;
  }
  if(movementDirection < 0){//moving backward, drop bomb with slight backward velocity
    nukeSpeed = -1 * speed;
  }
  
  //create bomb
  Bomb* flameSoldier = new Bomb(theBod->getX() + (theBod->getWidth() / 2), theBod->getY() + theBod->getHeight(), width / 3, height / 5, nukeSpeed);
  hellfireBrigade->push_back(flameSoldier);

}

      
void Helicopter::resetDirection(){

  movementDirection = 0;

}

    
void Helicopter::detectCollisions(XInfo& xinfo, Column* column){

  int columnX1 = column->getX();
  int columnX2 = column->getX() + column->getWidth();

  int columnY1 = column->getY();
  int columnY2 = column->getY() + column->getHeight();

  int siloX1 = columnX1;
  int siloX2 = columnX2;

  int siloY1 = columnY1 - column->getHeight();
  int siloY2 = columnY2;

  int heliX1 = theBod->getX();
  int heliX2 = heliX1 + theBod->getWidth();

  int heliY1 = theBod->getY();
  int heliY2 = heliY1 + theBod->getHeight();

  std::list<Bomb*>::iterator firstNuke = hellfireBrigade->begin();
  std::list<Bomb*>::iterator lastNuke = hellfireBrigade->end();

  if(!(hellfireBrigade->empty())){

    //check to see if any of your bombs have hit something
    for(firstNuke; firstNuke != lastNuke; firstNuke++){
      int bombX1 = (*firstNuke)->getX();
      int bombX2 = bombX1 + (*firstNuke)->getWidth();

      int bombY1 = (*firstNuke)->getY();
      int bombY2 = bombY1 + (*firstNuke)->getHeight();

      if((bombX1 < siloX2) && (bombX1 > siloX1)){

	if(column->hasGunner()){

	  if((bombY2 < siloY2) && (bombY2 > siloY1)){//one of your bombs has hit a silo

	    column->obliterate(xinfo, SILO);
	    firstNuke = hellfireBrigade->erase(firstNuke);
	    firstNuke--; continue;

	  }
	}

	if(bombY2 > columnY1){//one of your bombs has hit a building

	  column->obliterate(xinfo, BLOCK);
	  firstNuke = hellfireBrigade->erase(firstNuke);
	  firstNuke--;

	}
      }
    }
  }

  //check to see if you rockets have hit anything
  if(!(wolfpack->empty())){

    std::list<Rocket*>::iterator rocket = wolfpack->begin();

    for(int i = 0; i < wolfpack->size(); i++, rocket++){

      int rocketX1 = (*rocket)->getX();
      int rocketX2 = rocketX1 + (*rocket)->getWidth();

      int rocketY1 = (*rocket)->getY();
      int rocketY2 = rocketY1 + (*rocket)->getHeight();

      if((rocketX1 < siloX2) && (rocketX1 > siloX1)){

	if(column->hasGunner()){

	  if((rocketY2 < siloY2) && (rocketY2 > siloY1)){//one of your rockets has hit a silo

	    column->obliterate(xinfo, SILO);
	    rocket = wolfpack->erase(rocket);
	    rocket--; continue;

	  }
	}

	if(rocketY2 > columnY1){//one of your rockets has hit a building

	  column->obliterate(xinfo, BLOCK);
	  rocket = wolfpack->erase(rocket);
	  rocket--;

	}
      }
    }
  }

  if((heliX1 < columnX2) && (heliX1 > columnX1)){

    if(column->gotHealth(*theBod)){//got life!!!

      if((lifeblood->life + lifeblood->standardRefill) >= lifeblood->getWidth()){
	lifeblood->life = lifeblood->getWidth();
      }

      if((lifeblood->life + lifeblood->standardRefill) < lifeblood->getWidth()){
	lifeblood->life += lifeblood->standardRefill;
      }

      column->obliterate(xinfo, ORB);
    }

    if((heliY2 < columnY2) && (heliY2 > columnY1)){//you hit a building

      lifeblood->life -= (lifeblood->getWidth() / 15);
      column->obliterate(xinfo, BLOCK);

    }

    if(column->missileStrike(*theBod)){//you've been struck by a missile

      lifeblood->life -= (lifeblood->getWidth() / 10);

    }
  }
}

bool Helicopter::dead(){

  if(lifeblood->life < 0) return true;
  return false;

}


void Helicopter::incinerate(){

  Rocket* fang = new Rocket(theBod->getX() + (4 * (width / 6)), theBod->getY() + (theBod->getHeight() / 4), width / 7, theBod->getHeight() / 2);
  wolfpack->push_back(fang);

}

Helicopter::Helicopter(XInfo& xinfo, std::list<Column*>& displ) : displayables(displ){

  x = 100;
  y = 100;
  width = xinfo.windowWidth / 14;
  height = xinfo.windowHeight / 14;
  
  propster = new Propeller(x + (3 * (width / 6)), y, 3 * (width / 6), height / 5);
  theBod = new Body(x + (2 * (width / 6)), y + (2 * (height / 5)), 4 * (width / 6), 2 * (height / 5));
  whip = new Tail(x, y + (2 * (height / 5)), width / 6, 2 * (height / 5));

  hellfireBrigade = new std::list<Bomb*>();
  wolfpack = new std::list<Rocket*>();
  lifeblood = new HealthBar(width * 2, height / 3);
  movementDirection = 0;

}


Helicopter::~Helicopter(){

  delete wolfpack;
  delete hellfireBrigade;
  delete propster;
  delete theBod;
  delete whip;
  delete lifeblood;

}
