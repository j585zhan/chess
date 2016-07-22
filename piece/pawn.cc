#include "pawn.h"
#include <string>
#include <vector>

using namespace std;

Pawn::Pawn(int color, Coor coor, Board *b): color {color}, coor {coor}, b{b}{
	type = "P";
}

Pawn::~Pawn(){}

void Pawn::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> getAttackRange() {
	vector<Coor>attackRange;

	if (color == 0) {
		if (coor.y + 1 < 8 && coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y + 1)) {
			Coor oneMove = {coor.x + 1, coor.y + 1};
			attackRange.emplace(oneMove);
		}
		if (coor.y + 1 < 8 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y + 1)) {
			Coor oneMove = {coor.x - 1, coor.y + 1};
			attackRange.emplace(oneMove);
		}
	} else {
		if (coor.y - 1 >= 0 && coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y - 1)) {
			Coor oneMove = {coor.x + 1, coor.y - 1};
			attackRange.emplace(oneMove);
		}
		if (coor.y - 1 >= 0 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y - 1)) {
			Coor oneMove = {coor.x - 1, coor.y - 1};
			attackRange.emplace(oneMove);
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
				moveRange.emplace(oneMove);
			}
		}
		if ( coor.y + 1 < 8 && board->isEmpty(coor.x, coor.y + 1)) {
			Coor oneMove = {coor.x, coor.y + 1};
			moveRange.emplace(oneMove);
		}
	} else {
		if (coor.y == 6) {
			if (board->isEmpty(coor.x, coor.y - 2)) {
				Coor oneMove = {coor.x, coor.y - 2};
				moveRange.emplace(oneMove);
			}
		}
		
		if (coor.y - 1 >= 0 && board->isEmpty(coor.x, coor.y - 1)) {
			Coor oneMove = {coor.x, coor.y - 1};
			moveRange.emplace(oneMove);
		}
	}

	return moveRange;
}

string Pawn::getType() {
	return type;
}
