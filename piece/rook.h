#ifndef __ROOK_H__
#define __ROOK_H__
#include <vector>
#include "chesspiece.h"

class Rook: public ChessPiece {
  char type;
public:
  Rook(int color, Coor coor, Board *b);
  ~Rook();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  char getType();
};

#endif
