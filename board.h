#ifndef __BOARD_H__
#define __BOARD_H__
#include <vector>
#include <memory>
#include <string>
#include "view.h"
#include "ai.h"

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
  bool canMove();
  
public:
  std::vector<std::shared_ptr<View>> VecView;
  bool wturn;
  std::shared_ptr<AI> aiW;
  std::shared_ptr<AI> aiB;

  Board();
  ~Board();
  void scoreUpdate(int color, double score);
  bool isEmpty(int x, int y);
  bool isCheckmate();
  bool isCheck();
  void clearBoard();
  void initBoard();
  void notifyView(char piece, Coor c);
  void print();
  bool castling(Coor start, Coor dest);
  int resign(); // we need it here
  void placePiece(char piece, Coor pos);
  void removePiece(Coor pos);
  void undo(bool inter);
  bool isMove(Coor c);
  // makemove(start, dest) return "empty" if no piece at start, return invalid if
  //   the move is invlid
  std::string makeMove(Coor start, Coor dest);
  std::shared_ptr<ChessPiece> getPos(Coor c);
  int getBscore();
  int getWscore();
  void saveHistory();
    //std::vector<std::string> *getHistory();


  bool validBoard();
  bool needPromotion();
  void promote(char type);
  bool isStalemate();
  void setPlayer(const std::string &p1, const std::string &p2);

  friend class AI;
};

#endif
