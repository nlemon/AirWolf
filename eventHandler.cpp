#include<iostream>
#include"eventHandler.h"


EventHandler::EventHandler(Painter& guy, std::list<Column*>& things, Helicopter& heli) : luigi(guy), displayables(things), phoenix(heli), lastRepaint(0), end(0), FPS(30)
{}


unsigned long EventHandler::now(){

  timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;

}


void EventHandler::moveDisplayables(XInfo& xinfo){

  //move the helicopter
  phoenix.move(xinfo);

  std::list<Column*>::iterator firstDisplayable = displayables.begin();
  std::list<Column*>::iterator lastDisplayable = displayables.end();

  //move the columns over
  for(firstDisplayable; firstDisplayable != lastDisplayable; firstDisplayable++){

    (*firstDisplayable)->move(xinfo);

  }

}


void EventHandler::handleKeyPress(XInfo& xinfo, XEvent& event){

  int BufferSize = 10;
  KeySym key;
  char text[BufferSize];

  int i = XLookupString((XKeyEvent*)&event, text, BufferSize, &key, NULL);

  if(i == 1){

    switch(text[0]){

    case 'q':
      luigi.specialScreen(xinfo, GAMEOVER);

    //signal helicopter to torch those buildings
    case 'o':
      phoenix.nuke();
      break;

    //give em a face full of rocket fuel
    case 'p':
      phoenix.incinerate();
      break;

    //signal helicopter to move down
    case 's':
      phoenix.resetDirection();
      xinfo.setDirection(DOWN);
      break;

    //signal helicopter to move left
    case 'a':
      phoenix.resetDirection();
      xinfo.setDirection(LEFT);
      break;

    //signal helicopter to move up
    case 'w':
      phoenix.resetDirection();
      xinfo.setDirection(UP);
      break;

    //signal helicopter to move right
    case 'd':
      phoenix.resetDirection();
      xinfo.setDirection(RIGHT);
      break;

    //signal helicopter to halt 
    case 32:
      phoenix.resetDirection();
      xinfo.setDirection(NONE);
      break;

    //pause game
    case 'F':
    case 'f':
      luigi.specialScreen(xinfo, PAUSE);
      break;

    //set grader speed
    case 'g':
      xinfo.setAmateurSpeed();
      break;

    }

  }

}


void EventHandler::deal(XInfo& xinfo){
 
  luigi.repaint(xinfo);

  //deal with events
  while(true){
    if(XPending(xinfo.display) > 0){

      XNextEvent(xinfo.display, &event);

      switch(event.type){

        case KeyPress:
	  handleKeyPress(xinfo, event);	  
	  break;

      }
      
    }

    //move displayables
    moveDisplayables(xinfo);

    //repaint again if need be
    end = now();
    if((end - lastRepaint) > 1000000 / FPS){
      
      luigi.repaint(xinfo);
      lastRepaint = now();

    }

    //sleep if there's nothing to do
    if(!XPending(xinfo.display)){

      usleep((1000000 / FPS) - (end - lastRepaint));

    }
  }
}
