#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include <vector>
#include "board.h"

struct Coor{
  int x;
  int y;
};

class Chesspiece {
protected:
  int color;
  Coor coor;
  Board *board;
public:
  Chesspiece();
  virtual ~Chesspiece() = 0;
  virtual void makeMove() = 0;
  virtual void getAttackRange() = 0;
  virtual void getMoveRange() = 0;
  virtual std::string getType() = 0;
  Coor getCoor();
  int getColor();
};

#endif
