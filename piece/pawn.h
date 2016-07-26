#ifndef __PAWN_H__
#define __PAWN_H__
#include <vector>
#include "chesspiece.h"

class Pawn: public ChessPiece {
  char type;
  bool ep;
public:
  Pawn(int color, Coor coor, Board *b);
  ~Pawn();
  bool getEp();
  void makeMove(Coor dest);
  void closeEp();
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  char getType();
};

#endif
