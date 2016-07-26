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
		for (auto index : table) {
			if (board->makeMove(pPiece->getCoor(), allMoves.at(index)) == "") {
				return 1;
			}
		}
	}
	return 0;
}

int AI::moveLevel2() {
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
		auto moveR = pPiece->getMoveRange();
		auto attackR = pPiece->getAttackRange();
		// Try to check enemy king first
		for (auto trial : moveR) {
			string status = board->makeMove(pPiece->getCoor(), trial);
			if (status == "") {
				if (board->isCheck()) return 723;
				else board->undo(false);
			} else continue;
		}
		// Try to capture enemy pieces first
		vector<int> table;
		for (int i = 0; i < attackR.size(); ++i) {
			table.emplace_back(i);
		}
		random_shuffle(table.begin(), table.end());
		for (auto index : table) {
			if (board->makeMove(pPiece->getCoor(), attackR.at(index)) == "") {
				return 2;
			}
		}
	}
	return moveLevel1();
}
int AI::moveLevel3() {
	//Check if any piece is under attack
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			auto pPiece = board->theChessBoard[i][j];
			if (!pPiece) continue;
			if (pPiece->getColor() != color) continue;
			if (inOppoARange(Coor {i, j})) {
				vector<Coor> allMoves;
				auto moveR = pPiece->getMoveRange();
				auto attackR = pPiece->getAttackRange();
				allMoves.reserve(moveR.size() + attackR.size());
				allMoves.insert(allMoves.end(), attackR.begin(), attackR.end());
				allMoves.insert(allMoves.end(), moveR.begin(), moveR.end());
				for (auto trial : allMoves) {
					string status = board->makeMove(pPiece->getCoor(), trial);
					if (status == "") {
						if (inOppoARange(pPiece->getCoor())) board->undo(false);
						else return 222;
					} else continue;

				}
			}
		}
	}

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
		auto moveR = pPiece->getMoveRange();
		auto attackR = pPiece->getAttackRange();
		vector<Coor> allMoves;
		allMoves.reserve(moveR.size() + attackR.size());
		allMoves.insert(allMoves.end(), attackR.begin(), attackR.end());
		allMoves.insert(allMoves.end(), moveR.begin(), moveR.end());		
		// Try to avoid been capture
		// try attacking move first
		for (auto trial : allMoves) {
			string status = board->makeMove(pPiece->getCoor(), trial);
			if (status == "") {
				if (inOppoARange(pPiece->getCoor())) board->undo(false);
				else return 444;
			} else continue;
		}
	}
	return moveLevel2();
}

bool AI::inOppoARange(Coor c) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			auto pPiece = board->theChessBoard[i][j];
			if (!pPiece) continue;
			if (pPiece->getColor() == color) continue;
			for (auto t : pPiece->getAttackRange()) {
				if (t.x == c.x && t.y == c.y) return true;
			}
		}
	}
	return false;
}

int AI::moveLevel4() {
 return 4;
}

int AI::value(ChessPiece *p) {
	if (p->getType() == 'P') return 1;
	if (p->getType() == 'B') return 3;
	if (p->getType() == 'N') return 3;
	if (p->getType() == 'R') return 5;
	if (p->getType() == 'Q') return 9;
	if (p->getType() == 'K') return 1000;
	else return 0;
}
