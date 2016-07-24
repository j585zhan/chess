#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <vector>
#include "chesspiece.h"

class Bishop: public ChessPiece {
  char type;
public:
  Bishop(int color, Coor coor, Board *b);
  ~Bishop();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  char getType();
};

#endif
