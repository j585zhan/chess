#ifndef __KING_H__
#define __KING_H__
#include <vector>
#include "Chesspiece.h"

class King: public Chesspiece {
  std::string type;
public:
  King(int color, Coor coor, Board *b);
  ~King();
  void makeMove(Coor dest);
  vector<Coor> getAttackRange();
  vector<Coor> getMoveRange();
  std::string getType();
};

#endif

