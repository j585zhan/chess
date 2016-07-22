#include "board.h"
#include <string>

using namespace std;

Board::Board() {
	bScore = 0; 
	wScore = 0;
}

Board::~Board(){}

void scoreUpdate(int color, double score) {
	if (color == 0) {
		wScore += score;
	} else {
		bScore += score;
	}
}

bool Board:isEmpty(int x, int y) {
	if (!theChessBoard[x][y]) {
		return true;
	}
	return false;
}

bool Board::isCheckmate(){}

bool Board::isCheck(){}//who is checking who

void Board::clearBoard(){
	// for (int i = 0; i < 8; i++) {
	// 	vector<shared_ptr<ChessPiece>> theLine;
	// 	for (int j = 0; j < 8; j++) {
	// 		theLine.append
	// 	}
	// }
}

void Board::initBoard(){
	// for (int i = 0; i < 8; i++) {
	// 	vector<shared_ptr<ChessPiece>> theLine;
	// 	for (int j = 0; j < 8; j++) {
	// 		theLine.append
	// 	}
	// }
}

int Board::getBscore() {
	return bScore;
}

int Board::getWscore() {
	return wScore;
}
