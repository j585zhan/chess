#ifndef __KING_H__
#define __KING_H__
#include <vector>
#include "chesspiece.h"

class King: public ChessPiece {
  char type;
public:
  King(int color, Coor coor, Board *b);
  ~King();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  char getType();
};

#endif

