#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <vector>
#include "Chesspiece.h"

class Bishop: public Chesspiece {
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
