#include "king.h"
#include <string>
#include <vector>

using namespace std;

King::King(int color, Coor coor, Board *b): ChessPiece(color, coor, b)  {
	type = 'K';
}

King::~King(){}

void King::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> King::getAttackRange() {
	vector<Coor>attackRange;
	if (coor.y - 1 >= 0 && coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y - 1)) {
		Coor oneMove = {coor.x + 1, coor.y - 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y - 1)) {
		Coor oneMove = {coor.x - 1, coor.y - 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x + 1 >= 0 && !board->isEmpty(coor.x + 1, coor.y + 1)) {
		Coor oneMove = {coor.x + 1, coor.y + 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y + 1)) {
		Coor oneMove = {coor.x - 1, coor.y + 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.x + 1 >= 0 && !board->isEmpty(coor.x + 1, coor.y)) {
		Coor oneMove = {coor.x + 1, coor.y};
		attackRange.emplace_back(oneMove);
	}
	if (coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y)) {
		Coor oneMove = {coor.x - 1, coor.y};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && !board->isEmpty(coor.x, coor.y + 1)) {
		Coor oneMove = {coor.x, coor.y + 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && !board->isEmpty(coor.x, coor.y - 1)) {
		Coor oneMove = {coor.x, coor.y - 1};
		attackRange.emplace_back(oneMove);
	}

	return attackRange;
}

vector<Coor> King::getMoveRange() {
	vector<Coor>moveRange;
	if (coor.y - 1 >= 0 && coor.x + 1 < 8 && board->isEmpty(coor.x + 1, coor.y - 1)) {
		Coor oneMove = {coor.x + 1, coor.y - 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y - 1)) {
		Coor oneMove = {coor.x - 1, coor.y - 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x + 1 >= 0 && board->isEmpty(coor.x + 1, coor.y + 1)) {
		Coor oneMove = {coor.x + 1, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y + 1)) {
		Coor oneMove = {coor.x - 1, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.x + 1 >= 0 && board->isEmpty(coor.x + 1, coor.y)) {
		Coor oneMove = {coor.x + 1, coor.y};
		moveRange.emplace_back(oneMove);
	}
	if (coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y)) {
		Coor oneMove = {coor.x - 1, coor.y};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && board->isEmpty(coor.x, coor.y + 1)) {
		Coor oneMove = {coor.x, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && board->isEmpty(coor.x, coor.y - 1)) {
		Coor oneMove = {coor.x, coor.y - 1};
		moveRange.emplace_back(oneMove);
	}

	return moveRange;
}

char King::getType() {
	return type;
}
