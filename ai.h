#ifndef __AI_H__
#define __AI_H__
#include <vector>

class ChessPiece;
class Board;

class AI {
  Board *board;
  int level
public:
  AI();
  ~AI();
  void makeMove();
  void openingMove();
  void moveLevel1();
  void moveLevel2();
  void moveLevel3();
  void moveLevel4();
  int value(ChessPiece *p);
};

#endif
