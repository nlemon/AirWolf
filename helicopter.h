#ifndef __HELICOPTER_H__
#define __HELICOPTER_H__

#include<iostream>
#include<list>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<cstdlib>
#include"xinfo.h"
#include"displayable.h"
#include"column.h"
#include"flags.h"

class Helicopter : public Displayable{

  class Propeller : public Displayable{

  public:
    void paint(XInfo&);
    void move(XInfo&);
    Propeller(int, int, int, int);

  };

  class Body : public Displayable{

   public:
    void paint(XInfo&);
    void move(XInfo&);
    Body(int, int, int, int);

  };

  class Tail : public Displayable{

   public:
    void paint(XInfo&);
    void move(XInfo&);
    Tail(int, int, int, int);

  };

  class Bomb : public Displayable{

  public:
    int nukeSpeed;
    void paint(XInfo&);
    void move(XInfo&);
    Bomb(int, int, int, int, int);

  };

  class HealthBar : public Displayable{

   public:
     int life;
     int fullRefill;
     int standardRefill;
     void paint(XInfo&);
     void move(XInfo&);
     HealthBar(int, int);

  };

  class Rocket : public Displayable{

   public:
    void paint(XInfo&);
    void move(XInfo&);
    Rocket(int, int, int, int);

  };

  Propeller* propster;
  Body* theBod;
  Tail* whip;
  HealthBar* lifeblood;
  std::list<Column*>& displayables;
  std::list<Bomb*>* hellfireBrigade;
  std::list<Rocket*>* wolfpack;
  const static int speed = 4;
  int movementDirection;
  
 public:
  void nuke();
  void incinerate();
  void detectCollisions(XInfo&, Column*);
  void resetDirection();
  bool dead();

  void paint(XInfo&);
  void move(XInfo&);

  Helicopter(XInfo&, std::list<Column*>&);
  ~Helicopter();

};

#endif
