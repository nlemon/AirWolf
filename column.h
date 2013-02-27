#ifndef __COLUMN_H__
#define __COLUMN_H__

#include<iostream>
#include<list>
#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<cstdlib>
#include<sys/time.h>
#include"xinfo.h"
#include"displayable.h"
#include"column.h"


class Column : public Displayable{

  class Block{

   public:
    int width, height;
    Block(int, int);

  };

  class Missile : public Displayable{

   public:
    void paint(XInfo&);
    void move(XInfo&);
    Missile(int, int, int, int);

  };

  class HealthOrb : public Displayable{

   public:
    void paint(XInfo&);
    void move(XInfo&);
    HealthOrb(int, int, int, int);

  };

  class Points : public Displayable{

   public:
    void paint(XInfo&);
    void move(XInfo&);
    Points(int, int, int, int);

  };

  int numberOfBlocks;
  Block* blockey;
  HealthOrb* orbo;
  Points* killTrophy;
  std::list<Missile*>* missiles;

 public:
  void obliterate(XInfo&, destroyable);
  bool hasGunner();
  bool missileStrike(Displayable&);
  bool gotHealth(Displayable&);
  void fireMissile();

  void paint(XInfo&);
  void move(XInfo&);

  Column(int, XInfo&);
  ~Column();

};

#endif
