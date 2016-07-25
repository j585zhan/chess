#include "ai.h"
#include "board.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

AI::AI(int level, int color, Board *board): level{level},
	color{color}, board{board} {}

AI::~AI() {}

void AI::makeMove() {
	if (level == 1) {
		moveLevel1();
	} else if (level == 2) {
		moveLevel2();
	} else if (level == 3) {
		moveLevel3();
	} else if (level == 4) {
		moveLevel4();
	}
}
void AI::openingMove();
void AI::moveLevel1() {
	// Create a vector of number from 1 to 64
	vector<int> pos;
	for (int i = 0; i < 64; ++i) {
		pos.emplace_back(i);
	}
	// Generate seed using current time
	srand(time(nullptr));
	random_shuffle(pos.begin(), pos.end());
	for (int i = 0; i < 64; ++i) {
		int x = pos.at() / 8;
		int y = pos.at() / 8;
		auto pPiece = board->boardStatus[x][y];
		if (!pPiece) continue;
		if (pPiece->getColor != color) continue;
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
		
	}
}

void AI::moveLevel2();
void AI::moveLevel3();
void AI::moveLevel4();
int AI::value(ChessPiece *p);
