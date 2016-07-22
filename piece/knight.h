#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <vector>
#include "board.h"
#include "Chesspiece.h"

class Knight: public Chesspiece {
  std::string type;
public:
  Knight(int color, Coor coor, Board *b);
  ~Knight();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  std::string getType();
  Coor getCoor();
  int getColor();
};

#endif
