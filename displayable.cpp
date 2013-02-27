#include<iostream>
#include"displayable.h"


int Displayable::getX(){

  return x;

}


int Displayable::getY(){

  return y;

}


int Displayable::getWidth(){

  return width;

}


int Displayable::getHeight(){

  return height;

}


Displayable::Displayable(){}


Displayable::Displayable(int xval, int yval, int w, int h){

  x = xval;
  y = yval;
  width = w;
  height = h;

}
