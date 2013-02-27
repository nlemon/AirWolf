#ifndef __PAINTER_H__
#define __PAINTER_H__

#include<iostream>
#include<list>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<string>
#include<sstream>
#include"xinfo.h"
#include"column.h"
#include"displayable.h"
#include"helicopter.h"

class Painter{

  std::list<Column*>& displayables;
  Helicopter& excalibur;

 public:
  void specialScreen(XInfo&, screenType);
  void repaint(XInfo& xinfo);
  Painter(std::list<Column*>&, Helicopter&);

};

#endif
