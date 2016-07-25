#include "queen.h"
#include <string>
#include <vector>

using namespace std;

Queen::Queen(int color, Coor coor, Board *b): ChessPiece(color, coor, b)  {
	type = 'Q';
}

Queen::~Queen(){}

void Queen::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> Queen::getAttackRange() {
	vector<Coor>attackRange;
	for (int i = coor.x + 1; i < 8; i++) {
		if (!board->isEmpty(i, coor.y)) {
			if (board->getPos(Coor{i, coor.y})->getColor() != color) {
				Coor oneMove = {i, coor.y};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
	}

	for (int i = coor.x - 1; i >= 0; i--) {
		if (!board->isEmpty(i, coor.y)) {
			if (board->getPos(Coor{i, coor.y})->getColor() != color) {
				Coor oneMove = {i, coor.y};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
	}

	for (int i = coor.y + 1; i < 8; i++) {
		if (!board->isEmpty(coor.x, i)) {
			if (board->getPos(Coor{coor.x, i})->getColor() != color) {
				Coor oneMove = {coor.x, i};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
	}

	for (int i = coor.y - 1; i >= 0; i--) {
		if (!board->isEmpty(coor.x, i)) {
			if (board->getPos(Coor{coor.x, i})->getColor() != color) {
				Coor oneMove = {coor.x, i};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
	}

	int i, j;

	i = coor.x + 1;
	j = coor.y + 1;
	while (i < 8 && j < 8) {
		if (!board->isEmpty(i, j)) {
			if (board->getPos(Coor{i, j})->getColor() != color) {
				Coor oneMove = {i, j};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
		i++;
		j++;
	}

	i = coor.x - 1;
	j = coor.y + 1;
	while (i >= 0 && j < 8) {
		if (!board->isEmpty(i, j)) {
			if (board->getPos(Coor{i, j})->getColor() != color) {
				Coor oneMove = {i, j};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
		i--;
		j++;
	}

	i = coor.x + 1;
	j = coor.y - 1;
	while (i < 8 && j >= 0) {
		if (!board->isEmpty(i, j)) {
			if (board->getPos(Coor{i, j})->getColor() != color) {
				Coor oneMove = {i, j};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
		i++;
		j--;
	}

	i = coor.x - 1;
	j = coor.y - 1;
	while (i >= 0 && j >= 0) {
		if (!board->isEmpty(i, j)) {
			if (board->getPos(Coor{i, j})->getColor() != color) {
				Coor oneMove = {i, j};
				attackRange.emplace_back(oneMove);
			}
			break;
		}
		i--;
		j--;
	}

	return attackRange;
}

vector<Coor> Queen::getMoveRange() {
	vector<Coor>moveRange;
	for (int i = coor.x + 1; i < 8; i++) {
		if (!board->isEmpty(i, coor.y)) break;
		Coor oneMove = {i, coor.y};
		moveRange.emplace_back(oneMove);
	}

	for (int i = coor.x - 1; i >= 0; i--) {
		if (!board->isEmpty(i, coor.y)) break;
		Coor oneMove = {i, coor.y};
		moveRange.emplace_back(oneMove);
	}

	for (int i = coor.y + 1; i < 8; i++) {
		if (!board->isEmpty(coor.x, i)) break;
		Coor oneMove = {coor.x, i};
		moveRange.emplace_back(oneMove);
	}

	for (int i = coor.y - 1; i >= 0; i--) {
		if (!board->isEmpty(coor.x, i)) break;
		Coor oneMove = {coor.x, i};
		moveRange.emplace_back(oneMove);
	}

	int i, j;

	i = coor.x + 1;
	j = coor.y + 1;
	while (i < 8 && j < 8) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		moveRange.emplace_back(oneMove);

		i++;
		j++;
	}

	i = coor.x - 1;
	j = coor.y + 1;
	while (i >= 0 && j < 8) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		moveRange.emplace_back(oneMove);

		i--;
		j++;
	}

	i = coor.x + 1;
	j = coor.y - 1;
	while (i < 8 && j >= 0) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		moveRange.emplace_back(oneMove);

		i++;
		j--;
	}

	i = coor.x - 1;
	j = coor.y - 1;
	while (i >= 0 && j >= 0) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		moveRange.emplace_back(oneMove);

		i--;
		j--;
	}

	return moveRange;
}

char Queen::getType() {
	return type;
}
