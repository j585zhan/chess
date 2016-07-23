#ifndef __ROOK_H__
#define __ROOK_H__
#include <vector>
#include "Chesspiece.h"

class Rook: public Chesspiece {
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
