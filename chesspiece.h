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
  std::shared_pointer<Board> board;
public:
  Chesspiece(int color, Coor coor, Board *b);
  virtual ~Chesspiece() = 0;
  virtual void makeMove() = 0;
  virtual vector<Coor> getAttackRange() = 0;
  virtual vector<Coor> getMoveRange() = 0;
  virtual char getType() = 0;
  Coor getCoor();
  int getColor();
};

#endif
