#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include<iostream>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<list>
#include<sys/time.h>
#include"painter.h"
#include"column.h"
#include"helicopter.h"
#include"flags.h"

class EventHandler{

  XEvent event;
  Painter& luigi;
  std::list<Column*>& displayables;
  Helicopter& phoenix;
  unsigned long lastRepaint, end;
  const int FPS;

 public:
  void moveDisplayables(XInfo& xinfo);
  void handleKeyPress(XInfo&, XEvent&);
  void deal(XInfo& xinfo);
  unsigned long now();
  EventHandler(Painter&, std::list<Column*>&, Helicopter& heli);

};

#endif
