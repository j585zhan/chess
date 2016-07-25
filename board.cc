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
#include "ai.h"

#ifdef TEXT
#include "textdisplay.h"
#endif

#ifdef GRAPHIC
#include "graphicdisplay.h"
#endif

#ifdef UNICODE
#include "unicodedisplay.h"
#endif


using namespace std;

Board::Board() {
	#ifdef TEXT
	VecView.emplace_back(make_shared<TextDisplay>());
    #endif
	#ifdef GRAPHIC
	VecView.emplace_back(make_shared<GraphicDisplay>());
	#endif
	#ifdef UNICODE
	VecView.emplace_back(make_shared<UnicodeDisplay>());
	#endif

	bScore = 0; 
	wScore = 0;
	wturn = true;
	ai1 = nullptr;
	ai2 = nullptr;
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

bool Board::isMove(Coor c) {
	auto curCp = theChessBoard[c.x][c.y];
	if (!curCp) return true;

	char type;
	int color;
	type = curCp->getType();
	color = curCp->getColor();
	for (int i = 0; i < history.size(); i++) {
		auto cp = history[i][c.x][c.y];
		if (!cp || 
			cp->getType() != type ||
			cp->getColor() != color) {
			return true;
		}
	}
	return false;
}

bool Board::canMove(){
	vector<Coor> Mrange;
	vector<Coor> Arange;
	Coor Kcoor;
	int Kcolor;
	if (wturn) {
		Kcolor = 0;
	} else {
		Kcolor = 1;
	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			auto pChessPiece = theChessBoard[i][j];
			if (!pChessPiece || pChessPiece->getColor() != Kcolor) continue;
			Mrange = pChessPiece->getMoveRange();
			Arange = pChessPiece->getAttackRange();
			Kcoor = pChessPiece->getCoor();
			//check all moveRange to protect king
			for (int i = 0; i < Mrange.size(); i++) {
				if (makeMove(Kcoor, Mrange[i]) != "invalid") {
					undo(false);
					return true;
				}
			}

			//check all attackRange to protect king
			for (int i = 0; i < Arange.size(); i++) {
				if (makeMove(Kcoor, Arange[i]) != "invalid") {
					undo(false);
					return true;
				}
			}
		}
	}
	return false;
}

bool Board::isStalemate() {
	return !canMove() && !isCheck();
	//return !isCheck() && isCheckmate();
}

bool Board::isCheckmate() {
	return !canMove() && isCheck();
	//return !isCheck() && isCheckmate();
}

bool Board::isCheck(){
	Coor Kcoor;
	int c;
	if (wturn) {
		c = 0;
	} else {
		c = 1;
	}

	for (int i = 0; i < 8; i++) {
	//find King coor
		for (int j = 0; j < 8; j++) {
			if (!theChessBoard[i][j]) continue;
			if (theChessBoard[i][j]->getColor() == c && 
				theChessBoard[i][j]->getType() == 'K') {
 				Kcoor = theChessBoard[i][j]->getCoor();
 			}
 		}
 	}

 	for (int i = 0; i < 8; i++) {
 		for (int j = 0; j < 8; j++) {
 			if (!theChessBoard[i][j]) continue;
 			if (theChessBoard[i][j]->getColor() == (c+1)%2) {
 				vector<Coor> Arange = theChessBoard[i][j]->getAttackRange();
 				for (int k = 0; k < Arange.size(); k++) {
 					if (Arange[k].x == Kcoor.x && Arange[k].y == Kcoor.y) {
 						return true;
 					}
 				}
 			}
 		}
 	}

	return false;
}

void Board::notifyView(char piece, Coor c) {
	for (auto v : VecView) {
		v->notify(piece, c);
	}
}

void Board::print() {
	for (auto v : VecView) {
		v->print();
	}
}

void Board::clearBoard(){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			shared_ptr<ChessPiece> temp;
			temp = nullptr;
			std::swap(theChessBoard[i][j], temp);
			Coor c {i, j};
			notifyView('E', c);
		}
	}
	history.clear();
}

void Board::undo(bool inter) {
	if (history.size() == 1) return;
	wturn = !wturn;
	history.pop_back();
	theChessBoard = history.back();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (!theChessBoard[i][j]) {
				notifyView('E', Coor{i, j});
				continue;
			}
			theChessBoard[i][j]->makeMove(Coor{i, j});
			char c = theChessBoard[i][j]->getType();
			if (theChessBoard[i][j]->getColor() == 1) {
				c += ('a' - 'A');
			}
			if (!inter) notifyView(c, theChessBoard[i][j]->getCoor());
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
				notifyView('E', Coor{i, j});
				theLine.emplace_back(cp);
				continue;
			}
			char chess = cp->getType();
			if (chessColor == 1) {
				chess -= ('A' - 'a');
			}
			notifyView(chess, Coor{i, j});
			theLine.emplace_back(cp);
		}
		theChessBoard.emplace_back(theLine);
	}
	history.emplace_back(theChessBoard);
}

int Board::getBscore() {
	return bScore;
}

int Board::getWscore() {
	return wScore;
}


// 0 means white, 1 means black
int Board::resign() {
	if (wturn) {
		scoreUpdate(1, 1);
		wturn = true;
		return 0;
	}
	scoreUpdate(0, 1);
	wturn = true;
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
	if (chessColor == 0) notifyView(piece, pos);
	else notifyView(piece - 'A' + 'a', pos);
	history.emplace_back(theChessBoard);
}

void Board::removePiece(Coor pos) {
	theChessBoard[pos.x][pos.y] = nullptr;
	notifyView('E', pos);
	history.emplace_back(theChessBoard);
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

	//check null
	if (theChessBoard[start.x][start.y] == nullptr) {
		return "empty";
	}

	//check if move others chesspiece
	if ((theChessBoard[start.x][start.y]->getColor() == 1 && wturn) ||
	    (theChessBoard[start.x][start.y]->getColor() == 0 && (!wturn))) {
		return "invalid";
	}

	//cout<<theChessBoard[start.x][start.y]->getType()<<endl;

	vector<Coor> Arange = theChessBoard[start.x][start.y]->getAttackRange();
	vector<Coor> Mrange = theChessBoard[start.x][start.y]->getMoveRange();
	for (int i = 0; i < Arange.size(); i++) {
		if (Arange[i].x == dest.x && Arange[i].y == dest.y) {
			theChessBoard[dest.x][dest.y] = nullptr;
			using std::swap;
			swap(theChessBoard[start.x][start.y], theChessBoard[dest.x][dest.y]);
			theChessBoard[dest.x][dest.y]->makeMove(dest);
			notifyView('E', start);

			char chess = theChessBoard[dest.x][dest.y]->getType();
			if (theChessBoard[dest.x][dest.y]->getColor() == 1) {
				chess -= ('A' - 'a');
			}
			//notifyView(chess,dest);

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

			history.emplace_back(theChessBoard);

			if (isCheck()) {
				wturn = !wturn;
				undo(true);
				return "invalid";
			}
			
			wturn = !wturn;
			notifyView(chess,theChessBoard[dest.x][dest.y]->getCoor());

			return "";
		}
	}

	for (int i = 0; i < Mrange.size(); i++) {
		if (Mrange[i].x == dest.x && Mrange[i].y == dest.y) {
			theChessBoard[dest.x][dest.y] = theChessBoard[start.x][start.y];
			theChessBoard[start.x][start.y] = nullptr;
			notifyView('E', start);
			char chess = theChessBoard[dest.x][dest.y]->getType();
			if (theChessBoard[dest.x][dest.y]->getColor() == 1) {
				chess -= ('A' - 'a');
			}
			
			
			theChessBoard[dest.x][dest.y]->makeMove(dest);


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

			history.emplace_back(theChessBoard);
			
			if (isCheck()) {
				wturn = !wturn;
				undo(true);
				return "invalid";
			}

			wturn = !wturn;

			notifyView(chess, theChessBoard[dest.x][dest.y]->getCoor());
			return "";
		}
	}
	return "invalid";
}


shared_ptr<ChessPiece> Board::getPos(Coor c) {
	return theChessBoard[c.x][c.y];
}

void Board::saveHistory() {
	history.emplace_back(theChessBoard);
}

bool Board::validBoard() {
	int numWKing = 0, numBKing = 0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			auto pPiece = theChessBoard[i][j];
			if (!pPiece) continue;
			// Count the number of Kings
			if (pPiece->getType() == 'K') {
				if (pPiece->getColor() == 0) numWKing++;
				if (pPiece->getColor() == 1) numBKing++;
			}
			// Is there any pawn on the first line or last line
			if (j == 0 || j == 7) {
				if (pPiece->getType() == 'P') {
					return false;
				}
			}
		}
	}
	if (numBKing != 1 || numWKing != 1) return false;
	// Neither King is in check
	if (isCheck()) return false;
	// Switch turn and check is the King is in Check
	wturn = !wturn;
	if (isCheck()) {
		wturn = !wturn; // Switch back and return false
		return false;
	}
	// Switch back and return true
	wturn = !wturn;
	return true;
}

bool Board::needPromotion() {
	for (int i = 0; i < 8; ++i) {
		auto pBottomPiece = theChessBoard[i][0];
		auto pTopPiece = theChessBoard[i][7];
		if (pBottomPiece != nullptr && pBottomPiece->getType() == 'P' 
			&& pBottomPiece->getColor() == 1) {
			return true;
		} else if (pTopPiece != nullptr && pTopPiece->getType() == 'P' 
			&& pTopPiece->getColor() == 0) {
			return true;
		}
	}
	return false;
}

void Board::setPlayer(const string &p1, const string &p2) {
	if (p1 == "human" && p2 == "human") return;
	if (p1 != "human") {
		int ai1level = p1[p1.length() - 1] - '0';
		ai1 = make_shared<AI>(ai1level, 0, this);
	}
	if (p2 != "human") {
		int ai2Level = p2[p2.length() - 1] - '0';
		ai2 = make_shared<AI>(ai2Level, 1, this);
	}
}
