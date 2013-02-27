#include<iostream>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<list>
#include"xinfo.h"
#include"displayable.h"
#include"column.h"
#include"painter.h"
#include"eventHandler.h"
#include"helicopter.h"
#include"flags.h"

int main(int argv, char* argc[]){
  
  XInfo* xinfo = new XInfo(argv, argc);

  //start game with coulmns in middle of screen 
  int currentX = xinfo->windowWidth / 2;
  std::list<Column*>* columns = new std::list<Column*>();

  //construct level
  for(int i = 0; i < 500; i++){

    Column* col = new Column(currentX, *xinfo);
    columns->push_back(col);
    currentX += col->getWidth();

  }

  Helicopter* airWolf = new Helicopter(*xinfo, *columns);
  Painter* mario = new Painter(*columns, *airWolf);
  EventHandler* God = new EventHandler(*mario, *columns, *airWolf);

  //turn auto repeat off to avoid auto-repeat lag
  XAutoRepeatOff(xinfo->display);

  //intro screen
  mario->specialScreen(*xinfo, PAUSE); 
  God->deal(*xinfo);

  XAutoRepeatOn(xinfo->display);

  XFlush(xinfo->display);
  sleep(10);
  XCloseDisplay(xinfo->display);

  //clean up
  delete columns;
  delete airWolf;
  //other classes are not complicated
  //let default destructors handle things

  return 0;

}
