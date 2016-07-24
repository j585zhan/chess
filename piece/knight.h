#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <vector>
#include "chesspiece.h"

class Knight: public ChessPiece {
  char type;
public:
  Knight(int color, Coor coor, Board *b);
  ~Knight();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  char getType();
};

#endif
