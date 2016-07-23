#ifndef __PAWN_H__
#define __PAWN_H__
#include <vector>
#include "Chesspiece.h"

class Pawn: public Chesspiece {
  std::string type;
public:
  Pawn(int color, Coor coor, Board *b);
  ~Pawn();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  std::string getType();
};

#endif
