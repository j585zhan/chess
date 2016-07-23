#include "board.h"
#include <string>

using namespace std;

Board::Board(Controller* controller):controller{controller} {
	bScore = 0; 
	wScore = 0;
	wturn = true;
}

Board::~Board(){}

void Board::scoreUpdate(int color, double score) {
	if (color == 0) {
		wScore += score;
	} else {
		bScore += score;
	}
}

bool Board::isEmpty(int x, int y) {
	if (!theChessBoard[x][y]) {
		return true;
	}
	return false;
}

bool Board::isCheckmate(){
	vector<ChessPiece> Mrange;
	if (wturn) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j].getColor() == 0 && 
					theChessBoard[i][j].getType() == 'K') {
					Mrange = theChessBoard[i][j].getMoveRange();
				}
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j].getColor() == 1 && 
					theChessBoard[i][j].getType() == 'K') {
					Kcoor = theChessBoard[i][j].getCoor();
				}
			}
		}
	}
	return (this.isCheck() && (Mrange.size() == 0));
}

bool Board::isCheck(){
	Coor Kcoor;
	if (wturn) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j].getColor() == 0 && 
					theChessBoard[i][j].getType() == 'K') {
					Kcoor = theChessBoard[i][j].getCoor();
				}
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j].getColor() == 1) {
					vector<ChessPiece> Arange = theChessBoard[i][j].getAttackRange();
					for (int k = 0; k < Arange.size(); k++) {
						if (Arange[k].x == Kcoor.x && Arange[k].y == Kcoor.y) {
							return true;
						}
					}
				}
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j].getColor() == 1 && 
					theChessBoard[i][j].getType() == 'K') {
					Kcoor = theChessBoard[i][j].getCoor();
				}
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j].getColor() == 0) {
					vector<ChessPiece> Arange = theChessBoard[i][j].getAttackRange();
					for (int k = 0; k < Arange.size(); k++) {
						if (Arange[k].x == Kcoor.x && Arange[k].y == Kcoor.y) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void Board::clearBoard(){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			theChessBoard = nullptr;
		}
	}
}

void Board::initBoard(){
	for (int i = 0; i < 8; i++) {
		vector<shared_ptr<ChessPiece>> theLine;
		for (int j = 0; j < 8; j++) {
			shared_ptr<ChessPiece> cp;
			int chessColor;
			if (j <= 3) {
				chessColor = 0;
			} else {
				chessColor = 1;
			}

			if (j == 0 || j == 7) {
				if (i == 0 || i == 7) {
					cp = new Rook(chessColor, coor{i, j}, this);
				} else if (i == 1 || i == 6) {
					cp = new Knight(chessColor, coor{i, j}, this);
				} else if (i == 2 || i == 5) {
					cp = new Bishop(chessColor, coor{i, j}, this);
				} else if (i == 3) {
					cp = new Queen(chessColor, coor{i, j}, this);
				} else{
					cp = new King(chessColor, coor{i, j}, this);
				}
			} else if (j == 1 || j == 6) {
				cp = new Pawn(chessColor, coor{i, j}, this);
			} else {
				cp = nullptr;
			}
			this.notifyView(cp.getType(), cp.getCoor());
			theLine.emplace_back(cp);
		}
		theChessBoard.emplace_back(theLine);
	}
}

void notifyView(char chess, Coor c) {
	controller->notify(chess, c);
}

int Board::resign() {
	if (wturn) {
		return 0;
	}	
	return 1; 
}

void Board::placePiece(char piece, Coor pos) {
	shared_ptr<ChessPiece> cp;
	if (piece == 'K') {
		cp = new King(chessColor, coor{i, j}, this); 
	} else if (piece == 'Q') {
		cp = new Queen(chessColor, coor{i, j}, this);
	} else if (piece == 'B') {
		cp = new Bishop(chessColor, coor{i, j}, this);
	} else if (piece == 'R') {
		cp = new Rook(chessColor, coor{i, j}, this);
	} else if (piece == 'N') {
		cp = new Knight(chessColor, coor{i, j}, this);
	} else {
		cp = new Pawn(chessColor, coor{i, j}, this);
	}
	theChessBoard[pos.x][pos.y] = cp;
}

void Board::removePiece(Coor pos) {
	theChessBoard[pos.x][pos.y] = nullptr;
	shared_ptr<> p = new 
}

string Board::makeMove(Coor start, Coor dest) {
	if (theChessBoard[start.x][start.y] == nullptr) {
		return "empty";
	}
	vector<Coor> Arange = theChessBoard[start.x][start.y]->getAttackRange
	vector<Coor> Mrange = theChessBoard[start.x][start.y]->getMoveRange
	for (int i = 0; i < Arange.size(); i++) {
		if (range[i].x == dest.x && range[i].y == dest.y) {
			theChessBoard[dest.x][dest.y] = theChessBoard[start.x][start.y];
			theChessBoard[start.x][start.y] = nullptr;
			this.notifyView(theChessBoard[start.x][start.y].getType(), theChessBoard[start.x][start.y].getCoor());
			this.notifyView(theChessBoard[dest.x][dest.y].getType(), theChessBoard[dest.x][dest.y].getCoor());
			wturn = !wturn;
			this.removePiece(range[i]);
			return "";
		}
	}

	for (int i = 0; i < Mrange.size(); i++) {
		if (range[i].x == dest.x && range[i].y == dest.y) {
			theChessBoard[dest.x][dest.y] = theChessBoard[start.x][start.y];
			theChessBoard[start.x][start.y] = nullptr;
			this.notifyView(theChessBoard[start.x][start.y].getType(), theChessBoard[start.x][start.y].getCoor());
			this.notifyView(theChessBoard[dest.x][dest.y].getType(), theChessBoard[dest.x][dest.y].getCoor());
			wturn = !wturn;
			return "";
		}
	}


	return "invalid";
}

int Board::getBscore() {
	return bScore;
}

int Board::getWscore() {
	return wScore;
}
