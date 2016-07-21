#ifndef __CHESSPIECE_H__
#define __CHESSPIECE_H__
#include <vector>

struct Coor{
  int x;
  int y
};

class Chesspiece {
  int color;
  std::string type;
  Coor coor;
  Board *board;
  std::vector<Coor> moveRange();
  std::vector<Coor> attackRange();
public:
  Chesspiece();
  ~Chesspiece();
  void makeMove():;
  void attackRange():
  void moveRange();
  std::string getType();
  Coor getCoor();
  int getColor();
};

#endif
