#include<iostream>
#include"painter.h"


Painter::Painter(std::list<Column*>& thingsToPaint, Helicopter& heli) : displayables(thingsToPaint), excalibur(heli){}


void Painter::specialScreen(XInfo& xinfo, screenType special){

  //clear screen
  XDrawRectangle(xinfo.display, xinfo.window, xinfo.reverseGC, 0, 0, xinfo.pixWidth, xinfo.pixHeight);

  if(special == GAMEOVER){
    
    //display game over screen
    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc, xinfo.windowWidth / 4, xinfo.windowHeight / 4, xinfo.windowWidth / 2, xinfo.windowHeight / 6);
    XDrawImageString(xinfo.display, xinfo.window, xinfo.gc, xinfo.windowWidth / 4, xinfo.windowHeight / 4, "GAME OVER", 9);

    std::string gameOverText("The terrorists won. North America was destroyed.");

    //get point total
    std::string stringPoints;
    int points = xinfo.pointTotal;
    std::stringstream ss(stringPoints);

    ss << points;
    ss >> stringPoints;

    std::string pointText("Point Total: ");
    pointText.append(stringPoints);

    XDrawImageString(xinfo.display, xinfo.window, xinfo.reverseGC, xinfo.windowWidth / 4, xinfo.windowHeight / 3, gameOverText.c_str(), gameOverText.size());
    XDrawImageString(xinfo.display, xinfo.window, xinfo.reverseGC, xinfo.windowWidth / 4, (xinfo.windowHeight / 3) + 15, pointText.c_str(), pointText.size());
    
    XFlush(xinfo.display);
    sleep(5);
    exit(0);

  }

  if(special == PAUSE){
    
    //display pause screen
    XFillRectangle(xinfo.display, xinfo.window, xinfo.gc, 0, 0, xinfo.windowWidth, xinfo.windowHeight);

    std::string pauseText[14] = {"Nathan Lemon 20325615", 
				 "Welcome to the world of AirWolf", 
				 "Controls:", 
				 "w - move helicopter up",
				 "a - move helicopter left",
				 "s - move helicopter down",
				 "d - move helicopter right",
				 "o - fire bombs",
				 "p - fire rockets",
				 "space - halt helicopter movement",
				 "f/F - pause game",
				 "g - enter grader mode",
				 "q - quit game",
				 "Have fun, and good luck. Don't let the terrorists win!!"};

    int currentY = 10;
    for(int i = 0 ; i < 14; i++){

      XDrawImageString(xinfo.display, xinfo.window, xinfo.reverseGC, 10, currentY, pauseText[i].c_str(), pauseText[i].size());
      currentY += 20;
    }

    XFlush(xinfo.display);
    sleep(15);
  }

}


void Painter::repaint(XInfo& xinfo){

  std::list<Column*>::const_iterator firstThing = displayables.begin();
  std::list<Column*>::const_iterator copy = displayables.begin();
  std::list<Column*>::const_iterator lastThing = displayables.end();

  //clear the screen
  XDrawRectangle(xinfo.display, xinfo.window, xinfo.reverseGC, 0, 0, xinfo.pixWidth, xinfo.pixHeight);

  //create pixmap
  XFreePixmap(xinfo.display, xinfo.pixie);
  int depth = DefaultDepth(xinfo.display, DefaultScreen(xinfo.display));
  xinfo.pixie = XCreatePixmap(xinfo.display, xinfo.window, xinfo.pixWidth, xinfo.pixHeight, depth);
  XFillRectangle(xinfo.display, xinfo.pixie, xinfo.reverseGC, 0, 0, xinfo.pixWidth, xinfo.pixHeight);

  //paint the displayables
  for(int i = 0; i < 17; i++, firstThing++){//there are at most 16 columns per screen

    //check for collisions
    excalibur.detectCollisions(xinfo, *firstThing);

    //check health
    if(excalibur.dead()){

      excalibur.paint(xinfo);
      specialScreen(xinfo, GAMEOVER);

    }

    //paint
    (*firstThing)->paint(xinfo);

  }

  excalibur.paint(xinfo);

  if(displayables.front()->getX() < (0 - displayables.front()->getWidth())){
  displayables.pop_front();
  }

  //copy the pixmap over
  XCopyArea(xinfo.display, xinfo.pixie, xinfo.window, xinfo.gc, 0, 0, xinfo.pixWidth, xinfo.pixHeight, 0, 0);

  XFlush(xinfo.display);

}
