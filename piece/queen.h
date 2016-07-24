#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <vector>
#include "chesspiece.h"

class Queen: public ChessPiece {
  char type;
public:
  Queen(int color, Coor coor, Board *b);
  ~Queen();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  char getType();
};

#endif
