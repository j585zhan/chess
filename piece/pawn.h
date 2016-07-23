#ifndef __PAWN_H__
#define __PAWN_H__
#include <vector>
#include "Chesspiece.h"

class Pawn: public Chesspiece {
  char type;
public:
  Pawn(int color, Coor coor, Board *b);
  ~Pawn();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  char getType();
};

#endif
