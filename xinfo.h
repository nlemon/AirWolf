#ifndef __XINFO_H__
#define __XINFO_H__

#include<iostream>
#include<vector>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<sys/time.h>
#include"flags.h"

class XInfo{

 public:
  Display* display;
  int screen;
  Window window;

  unsigned long white, black;
  int border;
  int windowWidth, windowHeight;

  GC gc;
  GC reverseGC;

  Pixmap pixie;
  int pixWidth;
  int pixHeight;

  movement direction;
  int pointTotal;

  int scrollingSpeed;
  int missileFrequency;

  void setAmateurSpeed();
  void addToPointTotal();
  void setDirection(movement moveDirection);
  XInfo(int, char**);

};

#endif
