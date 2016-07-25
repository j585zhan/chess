#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include <string>
#include "view.h"

struct Coor{
  int x;
  int y;
};

class ChessPiece;

class Board {
  std::vector<std::vector<std::shared_ptr<ChessPiece>>> theChessBoard;  // The actual Board.
  double bScore;//up  = 1
  double wScore;//down  = 0
  std::vector<std::vector<std::vector<std::shared_ptr<ChessPiece>>>> history;
  
public:
  std::vector<std::shared_ptr<View>> VecView;

  Board();
  ~Board();
  bool wturn;
  void scoreUpdate(int color, double score);
  bool isEmpty(int x, int y);
  bool isCheckmate();
  bool isCheck();
  void clearBoard();
  void initBoard();
  void notifyView(char piece, Coor c);
  void print();
  int resign(); // we need it here
  void placePiece(char piece, Coor pos);
  void removePiece(Coor pos);
  void undo(bool inter);
  // makemove(start, dest) return "empty" if no piece at start, return invalid if
  //   the move is invlid
  //std::vector<Coor> Board::isSafe(Coor start, std::vector<Coor> dest);
  std::string makeMove(Coor start, Coor dest);
  int getBscore();
  int getWscore();
    //std::vector<std::string> *getHistory();


  // TODO: FUCK THIS SHIT
  bool validBoard() { return true; }
  bool isStalemate() { return false; }
  void setPlayer(const std::string& s1, const std::string& s2) {}

};

#endif
