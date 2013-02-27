#include<iostream>
#include"xinfo.h"

void XInfo::setDirection(movement moveDirection){

  direction = moveDirection;

}

void XInfo::setAmateurSpeed(){

  scrollingSpeed = 4;
  missileFrequency = 20;

}

void XInfo::addToPointTotal(){

  pointTotal += 50;

}

XInfo::XInfo(int argc, char* argv[]){

  //attemp to open the display
  display = XOpenDisplay("");
  if(!display){
    std::cerr << "can't open display" << std::endl;
  }

  //grab the screen associated with the display
  screen = DefaultScreen(display);

  //create the window
  white = XWhitePixel(display, screen);
  black = XBlackPixel(display, screen);
  border = 5;
  windowWidth = 900;
  windowHeight = 500;

  window = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, windowWidth, windowHeight, border, white, black);

  //set window properties
  XSetStandardProperties(display, window, "AirWolf", "...", None, argv, argc, NULL);

  //create graphics context
  gc = XCreateGC(display, window, 0, 0);
  XSetForeground(display, gc, WhitePixel(display, screen));
  XSetBackground(display, gc, BlackPixel(display, screen));
  XSetFillStyle(display, gc, FillSolid);
  XSetLineAttributes(display, gc, 1, LineSolid, CapButt, JoinRound);

  reverseGC = XCreateGC(display, window, 0, 0);
  XSetForeground(display, reverseGC, BlackPixel(display, screen));
  XSetBackground(display, reverseGC, WhitePixel(display, screen));
  XSetFillStyle(display, reverseGC, FillSolid);
  XSetLineAttributes(display, reverseGC, 1, LineSolid, CapButt, JoinRound);

  //create pixmap
  int depth = DefaultDepth(display, DefaultScreen(display));
  pixWidth = windowWidth;
  pixHeight = windowHeight;
  pixie = XCreatePixmap(display, window, pixWidth, pixHeight, depth);
  
  //tell the window which events you are interested in
  XSelectInput(display, window, KeyPressMask);

  //various flags used in the simulation
  direction = NONE;
  scrollingSpeed = 4;
  missileFrequency = 6;
  pointTotal = 0;

  //map window to screen
  XMapWindow(display, window);
  XFlush(display);
  sleep(2);

}
