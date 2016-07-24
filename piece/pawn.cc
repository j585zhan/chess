#include "pawn.h"
#include <string>
#include <vector>

using namespace std;

Pawn::Pawn(int color, Coor coor, Board *b): ChessPiece(color, coor, b) {
	type = 'P';
}

Pawn::~Pawn(){}

void Pawn::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> Pawn::getAttackRange() {
	vector<Coor>attackRange;

	if (color == 0) {
		if (coor.y + 1 < 8 && coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y + 1)) {
			Coor oneMove = {coor.x + 1, coor.y + 1};
			attackRange.emplace_back(oneMove);
		}
		if (coor.y + 1 < 8 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y + 1)) {
			Coor oneMove = {coor.x - 1, coor.y + 1};
			attackRange.emplace_back(oneMove);
		}
	} else {
		if (coor.y - 1 >= 0 && coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y - 1)) {
			Coor oneMove = {coor.x + 1, coor.y - 1};
			attackRange.emplace_back(oneMove);
		}
		if (coor.y - 1 >= 0 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y - 1)) {
			Coor oneMove = {coor.x - 1, coor.y - 1};
			attackRange.emplace_back(oneMove);
		}
	}
	return attackRange;
}

vector<Coor> Pawn::getMoveRange() {
	vector<Coor>moveRange;
	if (color == 0) {
		if (coor.y == 1) {
			if (board->isEmpty(coor.x, coor.y + 2)) {
				Coor oneMove = {coor.x, coor.y + 2};
				moveRange.emplace_back(oneMove);
			}
		}
		if ( coor.y + 1 < 8 && board->isEmpty(coor.x, coor.y + 1)) {
			Coor oneMove = {coor.x, coor.y + 1};
			moveRange.emplace_back(oneMove);
		}
	} else {
		if (coor.y == 6) {
			if (board->isEmpty(coor.x, coor.y - 2)) {
				Coor oneMove = {coor.x, coor.y - 2};
				moveRange.emplace_back(oneMove);
			}
		}
		
		if (coor.y - 1 >= 0 && board->isEmpty(coor.x, coor.y - 1)) {
			Coor oneMove = {coor.x, coor.y - 1};
			moveRange.emplace_back(oneMove);
		}
	}

	return moveRange;
}

char Pawn::getType() {
	return type;
}
