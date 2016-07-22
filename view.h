#ifndef __VIEW_H__
#define __VIEW_H__

struct Coor;

class View {

public:
  View();
  ~View();
  virtual void notify(char piece, Coor coor) = 0;
  virtual void print() = 0;
};

#endif
