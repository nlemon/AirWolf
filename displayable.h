#ifndef __DISPLAYABLE_H__
#define __DISPLAYABLE_H__

#include<iostream>
#include"xinfo.h"
#include"flags.h"

class Displayable{

 protected:

  int x, y, width, height;

 public:
  
  //pure virtual functions
  virtual void paint(XInfo& xinfo) = 0;
  virtual void move(XInfo& xinfo) = 0;

  //optionally implemented functions
  int getX();
  int getY();
  int getWidth();
  int getHeight();

  //constructors
  Displayable();
  Displayable(int, int, int, int);

};

#endif
