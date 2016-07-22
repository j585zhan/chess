#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include "chesspiece.h"

class Board {
  vector <std::shared_ptr<vector<std::shared_ptr<ChessPiece>>>> theChessBoard;  // The actual Board.
  double bScore;//up  = 1
  double wScore;//down  = 0
  //std::std::vector<std::string> history;
public:
  Board();
  ~Board();

  void scoreUpdate(int color, double score);
  bool isEmpty(int x, int y);
  bool isCheckmate();
  bool isCheck();
  void clearBoard();
  void initBoard();
  //void resign(); go to controller
  int getBscore();
  int getWscore();
  //std::vector<std::string> *getHistory();
};

#endif
