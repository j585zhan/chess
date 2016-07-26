#ifndef __AI_H__
#define __AI_H__
#include <vector>

class ChessPiece;
class Board;
class Coor;

class AI {
  int level;
  int color;
  Board *board;
public:
  AI(int level, int color, Board *board);
  ~AI();
  int makeMove();
  void openingMove();
  int moveLevel1();
  int moveLevel2();
  int moveLevel3();
  int moveLevel4();
  int value(ChessPiece *p);
  bool inOppoARange(Coor c);
};

#endif
