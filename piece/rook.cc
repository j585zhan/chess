#include "rook.h"
#include <string>
#include <vector>

using namespace std;

Rook::Rook(int color, Coor coor, Board *b): color {color}, coor {coor}, b{b}{
	type = "R";
}

Rook::~Rook(){}

void Rook::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> Rook::getAttackRange() {
	vector<Coor>attackRange;
	for (int i = coor.x + 1; i < 8; i++) {
		if (!board->isEmpty(i, coor.y)) {
			Coor oneMove = {i, coor.y};
			attackRange.emplace(oneMove);
			break;
		}
	}

	for (int i = coor.x - 1; i >= 0; i--) {
		if (!board->isEmpty(i, coor.y)) {
			Coor oneMove = {i, coor.y};
			attackRange.emplace(oneMove);
			break;
		}
	}

	for (int i = coor.y + 1; i < 8; i++) {
		if (!board->isEmpty(coor.x, i)) {
			Coor oneMove = {coor.x, i};
			attackRange.emplace(oneMove);
			break;
		}
	}

	for (int i = coor.y - 1; i >= 0; i--) {
		if (!board->isEmpty(coor.x, i)) {
			Coor oneMove = {coor.x, i};
			attackRange.emplace(oneMove);
			break;
		}
	}

	return attackRange;
}

vector<Coor> Rook::getMoveRange() {
	vector<Coor>moveRange;
	for (int i = coor.x + 1; i < 8; i++) {
		if (!board->isEmpty(i, coor.y)) break;
		Coor oneMove = {i, coor.y};
		moveRange.emplace(oneMove);
	}

	for (int i = coor.x - 1; i >= 0; i--) {
		if (!board->isEmpty(i, coor.y)) break;
		Coor oneMove = {i, coor.y};
		moveRange.emplace(oneMove);
	}

	for (int i = coor.y + 1; i < 8; i++) {
		if (!board->isEmpty(coor.x, i)) break;
		Coor oneMove = {coor.x, i};
		moveRange.emplace(oneMove);
	}

	for (int i = coor.y - 1; i >= 0; i--) {
		if (!board->isEmpty(coor.x, i)) break;
		Coor oneMove = {coor.x, i};
		moveRange.emplace(oneMove);
	}

	return moveRange;
}

string Rook::getType() {
	return type;
}
