#include <string>
#include <iostream>

#include "board.h"
#include "chesspiece.h"
#include "controller.h"
#include "piece/rook.h"
#include "piece/bishop.h"
#include "piece/king.h"
#include "piece/knight.h"
#include "piece/pawn.h"
#include "piece/queen.h"
#include "view.h"
#include "textdisplay.h"

using namespace std;

Board::Board(std::shared_ptr<View> view):view{view} {
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
	vector<Coor> Mrange;
	Coor Kcoor;
	if (wturn) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j]->getColor() == 0 && 
					theChessBoard[i][j]->getType() == 'K') {
					Mrange = theChessBoard[i][j]->getMoveRange();
				}
			}
		}
	} else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j]->getColor() == 1 && 
					theChessBoard[i][j]->getType() == 'K') {
					Kcoor = theChessBoard[i][j]->getCoor();
				}
			}
		}
	}
	return (isCheck() && (Mrange.size() == 0));
}

bool Board::isCheck(){
	// Coor Kcoor;
	// if (wturn) {
	// 	for (int i = 0; i < 8; i++) {
	// 	//find King coor
	// 		for (int j = 0; j < 8; j++) {
	// 			if (!theChessBoard[i][j]) continue;
	// 			if (theChessBoard[i][j]->getColor() == 0 && 
	// 				theChessBoard[i][j]->getType() == 'K') {
	// 				Kcoor = theChessBoard[i][j]->getCoor();
	// 			}
	// 		}
	// 	}

	// 	for (int i = 0; i < 8; i++) {
	// 		for (int j = 0; j < 8; j++) {
	// 			if (!theChessBoard[i][j]) continue;
	// 			if (theChessBoard[i][j]->getColor() == 1) {
	// 				vector<Coor> Arange = theChessBoard[i][j]->getAttackRange();
	// 				for (int k = 0; k < Arange.size(); k++) {
	// 					if (Arange[k].x == Kcoor.x && Arange[k].y == Kcoor.y) {
	// 						return true;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// } else {
	// 	for (int i = 0; i < 8; i++) {
	// 		for (int j = 0; j < 8; j++) {
	// 			if (!theChessBoard[i][j]) continue;
	// 			if (theChessBoard[i][j]->getColor() == 1 && 
	// 				theChessBoard[i][j]->getType() == 'K') {
	// 				Kcoor = theChessBoard[i][j]->getCoor();
	// 			}
	// 		}
	// 	}

	// 	for (int i = 0; i < 8; i++) {
	// 		for (int j = 0; j < 8; j++) {
	// 			if (!theChessBoard[i][j]) continue;
	// 			if (theChessBoard[i][j]->getColor() == 0) {
	// 				vector<Coor> Arange = theChessBoard[i][j]->getAttackRange();
	// 				for (int k = 0; k < Arange.size(); k++) {
	// 					if (Arange[k].x == Kcoor.x && Arange[k].y == Kcoor.y) {
	// 						return true;
	// 					}
	// 				}
	// 			}
	// 		}
	// 	}
	// }
	return false;
}

void Board::clearBoard(){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			theChessBoard[i][j] = nullptr;
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
					cp = std::make_shared<Rook>(chessColor, Coor{i, j}, this);
				} else if (i == 1 || i == 6) {
					cp = std::make_shared<Knight>(chessColor, Coor{i, j}, this);
				} else if (i == 2 || i == 5) {
					cp = std::make_shared<Bishop>(chessColor, Coor{i, j}, this);
				} else if (i == 3) {
					cp = std::make_shared<Queen>(chessColor, Coor{i, j}, this);
				} else{
					cp = std::make_shared<King>(chessColor, Coor{i, j}, this);
				}
			} else if (j == 1 || j == 6) {
				cp = std::make_shared<Pawn>(chessColor, Coor{i, j}, this);
			} else {
				cp = nullptr;
				view->notify('E', Coor{i, j});
				theLine.emplace_back(cp);
				continue;
			}
			view->notify(cp->getType(), Coor{i, j});
			theLine.emplace_back(cp);
		}
		theChessBoard.emplace_back(theLine);
	}

	#ifdef DEBUG
	// for (int i = 0; i < 8; ++i) {
	// 	for (int j = 0; j < 8; ++j) {
	// 		if (!theChessBoard[i][j]) cout << " ";
	// 		else theChessBoard[i]
	// 	}
	// }
	#endif
}

int Board::resign() {
	if (wturn) {
		return 0;
	}	
	return 1; 
}

void Board::placePiece(char piece, Coor pos) {
	shared_ptr<ChessPiece> cp;
	int chessColor = 0;
	if (piece >= 'A' && piece <= 'Z') chessColor = 0;
	else {
		chessColor = 1;
		piece -= 'a';
		piece += 'A';
	}
	if (piece == 'K') {
		cp = std::make_shared<King>(chessColor, pos, this); 
	} else if (piece == 'Q') {
		cp = std::make_shared<Queen>(chessColor, pos, this);
	} else if (piece == 'B') {
		cp = std::make_shared<Bishop>(chessColor, pos, this);
	} else if (piece == 'R') {
		cp = std::make_shared<Rook>(chessColor, pos, this);
	} else if (piece == 'N') {
		cp = std::make_shared<Knight>(chessColor, pos, this);
	} else {
		cp = std::make_shared<Pawn>(chessColor, pos, this);
	}
	theChessBoard[pos.x][pos.y] = cp;
}

void Board::removePiece(Coor pos) {
	theChessBoard[pos.x][pos.y] = nullptr;
}

string Board::makeMove(Coor start, Coor dest) {

	#ifdef DEBUG
	int size = 8;
	for (int i = size - 1; i >= 0; --i) {
		cout << i + 1<< ' ';
		for (int j = 0; j < size; ++j) {
			if (!theChessBoard[j][i]) cout << " ";
			else cout << theChessBoard[j][i]->getType();
		}
		cout << endl;
	}
	cout << "start: " << start.x << " " << start.y << endl;
	cout << "dest: " << dest.x << " " << dest.y << endl;
	#endif

	if (theChessBoard[start.x][start.y] == nullptr) {
		return "empty";
	}
	cout<<theChessBoard[start.x][start.y]->getType()<<endl;

	vector<Coor> Arange = theChessBoard[start.x][start.y]->getAttackRange();
	vector<Coor> Mrange = theChessBoard[start.x][start.y]->getMoveRange();
	for (int i = 0; i < Arange.size(); i++) {
		if (Arange[i].x == dest.x && Arange[i].y == dest.y) {
			theChessBoard[dest.x][dest.y] = theChessBoard[start.x][start.y];
			theChessBoard[start.x][start.y] = nullptr;
			view->notify('E', start);
			view->notify(theChessBoard[dest.x][dest.y]->getType(), theChessBoard[dest.x][dest.y]->getCoor());
			wturn = !wturn;

			#ifdef DEBUG
			for (int i = size - 1; i >= 0; --i) {
				cout << i + 1<< ' ';
				for (int j = 0; j < size; ++j) {
					if (!theChessBoard[j][i]) cout << " ";
					else cout << theChessBoard[j][i]->getType();
				}
				cout << endl;
			}
			#endif

			return "";
		}
	}

	for (int i = 0; i < Mrange.size(); i++) {
		if (Mrange[i].x == dest.x && Mrange[i].y == dest.y) {
			theChessBoard[dest.x][dest.y] = theChessBoard[start.x][start.y];
			theChessBoard[start.x][start.y] = nullptr;
			view->notify('E', start);
			//The dest at the last should be ----> theChessBoard[dest.x][dest.y]->getCoor()
			// you need to check the coorindate of the piece!!!!!
			// This will work for now but it is the wrong idea
			view->notify(theChessBoard[dest.x][dest.y]->getType(), dest);
			wturn = !wturn;

			#ifdef DEBUG
			for (int i = size - 1; i >= 0; --i) {
				cout << i + 1<< ' ';
				for (int j = 0; j < size; ++j) {
					if (!theChessBoard[j][i]) cout << " ";
					else cout << theChessBoard[j][i]->getType();
				}
				cout << endl;
			}
			#endif

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
