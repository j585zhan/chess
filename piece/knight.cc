#include "knight.h"
#include <string>
#include <vector>

using namespace std;

Knight::Knight(int color, Coor coor, Board *b): ChessPiece(color, coor, b) {
	type = 'N';
}

Knight::~Knight(){}

void Knight::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> Knight::getAttackRange() {
	vector<Coor> attackRange;
	if (coor.y - 1 >= 0 && coor.x + 2 < 8 && !board->isEmpty(coor.x + 2, coor.y - 1)) {
		Coor oneMove = {coor.x + 2, coor.y - 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && coor.x - 2 >= 0 && !board->isEmpty(coor.x - 2, coor.y - 1)) {
		Coor oneMove = {coor.x - 2, coor.y - 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x + 2 >= 0 && !board->isEmpty(coor.x + 2, coor.y + 1)) {
		Coor oneMove = {coor.x + 2, coor.y + 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x - 2 >= 0 && !board->isEmpty(coor.x - 2, coor.y + 1)) {
		Coor oneMove = {coor.x - 2, coor.y + 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y - 2 >= 0 && coor.x + 1 >= 0 && !board->isEmpty(coor.x + 1, coor.y - 2)) {
		Coor oneMove = {coor.x + 1, coor.y - 2};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y - 2 >= 0 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y - 2)) {
		Coor oneMove = {coor.x - 1, coor.y - 2};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 2 >= 0 && coor.x + 1 >= 0 && !board->isEmpty(coor.x + 1, coor.y + 2)) {
		Coor oneMove = {coor.x + 1, coor.y + 2};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 2 >= 0 && coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y + 2)) {
		Coor oneMove = {coor.x - 1, coor.y + 2};
		attackRange.emplace_back(oneMove);
	}

	return attackRange;
}


vector<Coor> Knight::getMoveRange() {
	vector<Coor>moveRange;
	if (coor.y - 1 >= 0 && coor.x + 2 < 8 && board->isEmpty(coor.x + 2, coor.y - 1)) {
		Coor oneMove = {coor.x + 2, coor.y - 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && coor.x - 2 >= 0 && board->isEmpty(coor.x - 2, coor.y - 1)) {
		Coor oneMove = {coor.x - 2, coor.y - 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x + 2 >= 0 && board->isEmpty(coor.x + 2, coor.y + 1)) {
		Coor oneMove = {coor.x + 2, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 1 >= 0 && coor.x - 2 >= 0 && board->isEmpty(coor.x - 2, coor.y + 1)) {
		Coor oneMove = {coor.x - 2, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y - 2 >= 0 && coor.x + 1 >= 0 && board->isEmpty(coor.x + 1, coor.y - 2)) {
		Coor oneMove = {coor.x + 1, coor.y - 2};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y - 2 >= 0 && coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y - 2)) {
		Coor oneMove = {coor.x - 1, coor.y - 2};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 2 >= 0 && coor.x + 1 >= 0 && board->isEmpty(coor.x + 1, coor.y + 2)) {
		Coor oneMove = {coor.x + 1, coor.y + 2};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 2 >= 0 && coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y + 2)) {
		Coor oneMove = {coor.x - 1, coor.y + 2};
		moveRange.emplace_back(oneMove);
	}

	return moveRange;
}

char Knight::getType() {
	return type;
}
