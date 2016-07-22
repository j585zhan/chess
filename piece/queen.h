#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <vector>
#include "board.h"
#include "Chesspiece.h"

class Queen: public Chesspiece {
  std::string type;
public:
  Queen(int color, Coor coor, Board *b);
  ~Queen();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  std::string getType();
  Coor getCoor();
  int getColor();
};

#endif
