#include "pawn.h"
#include <string>
#include <vector>

using namespace std;

Pawn::Pawn(int color, Coor coor, Board *b): ChessPiece(color, coor, b) {
	type = 'P';
	ep = false;
}

Pawn::~Pawn(){}

void Pawn::closeEp() {
	ep = false;
}


void Pawn::makeMove(Coor dest) {
	if (dest.y - 2 == coor.y || dest.y + 2 == coor.y) {
		ep = true;
	}
	coor = dest;
}

bool Pawn::getEp() {
	return ep;
}

vector<Coor> Pawn::getAttackRange() {
	vector<Coor>attackRange;

	if (color == 0) {
		if (coor.y + 1 < 8 && coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y + 1)
			&& board->getPos(Coor{coor.x + 1, coor.y + 1})->getColor() != color) {
			Coor oneMove = {coor.x + 1, coor.y + 1};
			attackRange.emplace_back(oneMove);
		}
		if (coor.y + 1 < 8 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y + 1)
			&& board->getPos(Coor{coor.x - 1, coor.y + 1})->getColor() != color) {
			Coor oneMove = {coor.x - 1, coor.y + 1};
			attackRange.emplace_back(oneMove);
		}
		// fuck
		if (coor.y + 1 < 8 && coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y + 1) &&
			!board->isEmpty(coor.x - 1, coor.y) && board->getPos(Coor{coor.x - 1, coor.y})->getEp()) {
			Coor oneMove = {coor.x - 1, coor.y + 1};
			attackRange.emplace_back(oneMove);
		}
		if (coor.y + 1 < 8 && coor.x + 1 < 8 && board->isEmpty(coor.x + 1, coor.y + 1) &&
			!board->isEmpty(coor.x + 1, coor.y) && board->getPos(Coor{coor.x + 1, coor.y})->getEp()) {
			Coor oneMove = {coor.x + 1, coor.y + 1};
			attackRange.emplace_back(oneMove);
		}

	} else {
		if (coor.y - 1 >= 0 && coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y - 1)
			&& board->getPos(Coor{coor.x + 1, coor.y - 1})->getColor() != color) {
			Coor oneMove = {coor.x + 1, coor.y - 1};
			attackRange.emplace_back(oneMove);
		}
		if (coor.y - 1 >= 0 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y - 1)
			&& board->getPos(Coor{coor.x - 1, coor.y - 1})->getColor() != color) {
			Coor oneMove = {coor.x - 1, coor.y - 1};
			attackRange.emplace_back(oneMove);
		}
		if (coor.y - 1 >= 0 && coor.x + 1 < 8 && board->isEmpty(coor.x + 1, coor.y - 1) &&
			!board->isEmpty(coor.x + 1, coor.y) && board->getPos(Coor{coor.x + 1, coor.y})->getEp()) {
			Coor oneMove = {coor.x + 1, coor.y - 1};
			attackRange.emplace_back(oneMove);
		}
		if (coor.y - 1 >= 0 && coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y - 1) &&
			!board->isEmpty(coor.x - 1, coor.y) && board->getPos(Coor{coor.x - 1, coor.y})->getEp()) {
			Coor oneMove = {coor.x - 1, coor.y - 1};
			attackRange.emplace_back(oneMove);
		}
	}
	return attackRange;
}

vector<Coor> Pawn::getMoveRange() {
	vector<Coor>moveRange;
	if (color == 0) {
		if ( coor.y + 1 < 8 && board->isEmpty(coor.x, coor.y + 1)) {
			Coor oneMove = {coor.x, coor.y + 1};
			moveRange.emplace_back(oneMove);
			if (coor.y == 1) {
				if (board->isEmpty(coor.x, coor.y + 2)) {
					Coor oneMove = {coor.x, coor.y + 2};
					moveRange.emplace_back(oneMove);
				}
			}
		}
	} else {
		if (coor.y - 1 >= 0 && board->isEmpty(coor.x, coor.y - 1)) {
			Coor oneMove = {coor.x, coor.y - 1};
			moveRange.emplace_back(oneMove);
			if (coor.y == 6) {
				if (board->isEmpty(coor.x, coor.y - 2)) {
					Coor oneMove = {coor.x, coor.y - 2};
					moveRange.emplace_back(oneMove);
				}
			}
		}
	}

	return moveRange;
}

char Pawn::getType() {
	return type;
}
