#ifndef __BOARD_H__
#define __BOARD_H__
#include "board.h"
#include <vector>
#include "chesspiece.h"

class Board {
  std::vector<std::vector<ChessPiece>> theChessBoard;  // The actual Board.
  int bScore;
  int wScore;
  std::std::vector<std::string> history;
public:
  Board();
  ~Board();

  bool isCheckmate();
  bool isCheck();
  void clearBoard();
  void initBoard();
  void switchPlayer();
  void resign();
  int getBscore();
  int getWscore();
  std::vector<std::string> *getHistory();
};

#endif
