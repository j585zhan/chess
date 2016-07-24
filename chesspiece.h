#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include <vector>
#include "board.h"

using std::vector;

class ChessPiece {
protected:
  int color;
  Coor coor;
  std::shared_ptr<Board> board;
public:
  ChessPiece();
  ChessPiece(int color, Coor coor, Board *b);
  virtual ~ChessPiece() = 0;
  virtual void makeMove(Coor dest) = 0;
  virtual vector<Coor> getAttackRange() = 0;
  virtual vector<Coor> getMoveRange() = 0;
  virtual char getType() = 0;
  Coor getCoor();
  int getColor();
};

#endif
