#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <vector>
#include "board.h"
#include "Chesspiece.h"

class Bishop: public Chesspiece {
  std::string type;
public:
  Bishop(int color, Coor coor, Board *b);
  ~Bishop();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  std::string getType();
  Coor getCoor();
  int getColor();
};

#endif
