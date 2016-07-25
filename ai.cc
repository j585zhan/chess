#include "ai.h"
#include "board.h"
#include "chesspiece.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

AI::AI(int level, int color, Board *board): level{level},
	color{color}, board{board} {}

AI::~AI() {}

int AI::makeMove() {
	if (level == 1) {
		return moveLevel1();
	} else if (level == 2) {
		return moveLevel2();
	} else if (level == 3) {
		return moveLevel3();
	} else if (level == 4) {
		return moveLevel4();
	} else {
		return 0;
	}
}

void AI::openingMove() {}

int AI::moveLevel1() {
	// Create a vector of number from 1 to 64
	vector<int> pos;
	for (int i = 0; i < 64; ++i) {
		pos.emplace_back(i);
	}
	// Generate seed using current time
	srand(time(nullptr));
	random_shuffle(pos.begin(), pos.end());
	for (int i = 0; i < 64; ++i) {
		int x = pos.at(i) / 8;
		int y = pos.at(i) % 8;
		auto pPiece = board->theChessBoard[x][y];
		if (!pPiece) continue;
		if (pPiece->getColor() != color) continue;
		vector<Coor> allMoves;
		auto moveR = pPiece->getMoveRange();
		auto attackR = pPiece->getAttackRange();
		allMoves.reserve(moveR.size() + attackR.size());
		allMoves.insert(allMoves.end(), moveR.begin(), moveR.end());		
		allMoves.insert(allMoves.end(), attackR.begin(), attackR.end());		
		//Create a vector of number from 1 to size of allMoves
		vector<int> table;
		for (int i = 0; i < allMoves.size(); ++i) {
			table.emplace_back(i);
		}
		random_shuffle(table.begin(), table.end());
		for (int i = 0; i < allMoves.size(); ++i) {
			if (board->makeMove(pPiece->getCoor(), allMoves.at(table.at(i))) == "") {
				return 1;
			}
		}
	}
	return 0;
}

int AI::moveLevel2() {return 2;}
int AI::moveLevel3() {return 3;}
int AI::moveLevel4() {return 4;}
int AI::value(ChessPiece *p) {return 1;}
