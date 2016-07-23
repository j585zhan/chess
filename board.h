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
  bool wturn;
  void scoreUpdate(int color, double score);
  bool isEmpty(Coor c);
  bool isCheckmate();
  bool isCheck();
  void clearBoard();
  void initBoard();
  int resign(); // we need it here
  void placePiece(char piece, Coor pos);
  void removePiece(Coor pos);
  // makemove(start, dest) return "empty" if no piece at start, return invalid if
  //   the move is invlid
  std::string makeMove(Coor start, Coor dest);
  int getBscore();
  int getWscore();
    //std::vector<std::string> *getHistory();
};

#endif
