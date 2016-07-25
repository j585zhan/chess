#ifndef __AI_H__
#define __AI_H__
#include <vector>

class ChessPiece;
class Board;

class AI {
  int level;
  int color;
  Board *board;
public:
  AI(int level, int color, Board *board);
  ~AI();
  void makeMove();
  void openingMove();
  bool moveLevel1();
  void moveLevel2();
  void moveLevel3();
  void moveLevel4();
  int value(ChessPiece *p);
};

#endif
