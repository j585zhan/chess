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

Board::Board() {
	view = make_shared<TextDisplay>();
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
	return isCheck();
	//return (isCheck() && (Mrange.size() == 0));
}

bool Board::isCheck(){
	Coor Kcoor;
	//cout<<"ischeck"<<endl;
	if (wturn) {
		//cout<<"wturn"<<endl;
		for (int i = 0; i < 8; i++) {
		//find King coor
			for (int j = 0; j < 8; j++) {
				if (!theChessBoard[i][j]) continue;
				if (theChessBoard[i][j]->getColor() == 0 && 
					theChessBoard[i][j]->getType() == 'K') {
					//cout<<"king"<<endl;
	 				Kcoor = theChessBoard[i][j]->getCoor();
					//cout<<": "<<Kcoor.x<<Kcoor.y<<endl;
	 			}
	 		}
	 	}

	 	for (int i = 0; i < 8; i++) {
	 		for (int j = 0; j < 8; j++) {
	 			if (!theChessBoard[i][j]) continue;
	 			if (theChessBoard[i][j]->getColor() == 1) {
					//cout<<"ememy"<<theChessBoard[i][j]->getType()<<": "<<i<<" "<<j<<endl;
	 				vector<Coor> Arange = theChessBoard[i][j]->getAttackRange();
					//cout<<"getArange"<<endl;
	 				for (int k = 0; k < Arange.size(); k++) {
	 					if (Arange[k].x == Kcoor.x && Arange[k].y == Kcoor.y) {
	 						return true;
	 					}
	 				}
					//cout<<"safe"<<endl;
	 			}
	 		}
	 	}
	} else {
		//cout<<"bturn"<<endl;
	 	for (int i = 0; i < 8; i++) {
	 		for (int j = 0; j < 8; j++) {
	 			if (!theChessBoard[i][j]) continue;
	 			if (theChessBoard[i][j]->getColor() == 1 && 
	 				theChessBoard[i][j]->getType() == 'K') {
	 				//cout<<"king"<<endl;
					Kcoor = theChessBoard[i][j]->getCoor();
	 			}
	 		}
	 	}

	 	for (int i = 0; i < 8; i++) {
	 		for (int j = 0; j < 8; j++) {
	 			if (!theChessBoard[i][j]) continue;
	 			if (theChessBoard[i][j]->getColor() == 0) {
	 				vector<Coor> Arange = theChessBoard[i][j]->getAttackRange();
	 				for (int k = 0; k < Arange.size(); k++) {
	 					if (Arange[k].x == Kcoor.x && Arange[k].y == Kcoor.y) {
	 						return true;
	 					}
	 				}
	 			}
	 		}
		}
	}
	//cout<<"false"<<endl;
	return false;
}

void Board::clearBoard(){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			shared_ptr<ChessPiece> temp;
			temp = nullptr;
			std::swap(theChessBoard[i][j], temp);
			Coor c {i, j};
			view->notify('E', c);
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
			char chess = cp->getType();
			if (chessColor == 1) {
				chess -= ('A' - 'a');
			}
			view->notify(chess, Coor{i, j});
			theLine.emplace_back(cp);
		}
		theChessBoard.emplace_back(theLine);
	}
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
		
		return 0;
	}
	scoreUpdate(0, 1);
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
	if (chessColor == 0) view->notify(piece, pos);
	else view->notify(piece - 'A' + 'a', pos);
}

void Board::removePiece(Coor pos) {
	theChessBoard[pos.x][pos.y] = nullptr;
	view->notify('E', pos);
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

	if ((theChessBoard[start.x][start.y]->getColor() == 1 && wturn) ||
	    (theChessBoard[start.x][start.y]->getColor() == 0 && (!wturn))) {
		return "invalid";
	}

	cout<<theChessBoard[start.x][start.y]->getType()<<endl;

	vector<Coor> Arange = theChessBoard[start.x][start.y]->getAttackRange();
	vector<Coor> Mrange = theChessBoard[start.x][start.y]->getMoveRange();
	for (int i = 0; i < Arange.size(); i++) {
		if (Arange[i].x == dest.x && Arange[i].y == dest.y) {
			//theChessBoard[dest.x][dest.y] = nullptr;
			//cout<<0<<endl;
			using std::swap;
			swap(theChessBoard[start.x][start.y], theChessBoard[dest.x][dest.y]);
			//theChessBoard[dest.x][dest.y] = theChessBoard[start.x][start.y];
			//cout<<1<<endl;
			//theChessBoard[start.x][start.y] = nullptr;
			//cout<<2<<endl;
			theChessBoard[dest.x][dest.y]->makeMove(dest);
			//cout<<3<<endl;
			view->notify('E', start);

			char chess = theChessBoard[dest.x][dest.y]->getType();
			if (theChessBoard[dest.x][dest.y]->getColor() == 1) {
				chess -= ('A' - 'a');
			}
			//view->notify(chess,dest);

			view->notify(chess,theChessBoard[dest.x][dest.y]->getCoor());
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
			char chess = theChessBoard[dest.x][dest.y]->getType();
			if (theChessBoard[dest.x][dest.y]->getColor() == 1) {
				chess -= ('A' - 'a');
			}

			wturn = !wturn;
			
			
			theChessBoard[dest.x][dest.y]->makeMove(dest);

			view->notify(chess, theChessBoard[dest.x][dest.y]->getCoor());

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
