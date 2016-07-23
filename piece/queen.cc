#include "queen.h"
#include <string>
#include <vector>

using namespace std;

Queen::Queen(int color, Coor coor, Board *b): color {color}, coor {coor}, b{b}{
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

	int i, j;

	i = coor.x + 1;
	j = coor.y + 1;
	while (i < 8 && j < 8) {
		if (!board->isEmpty(i, j)) {
			Coor oneMove = {i, j};
			attackRange.emplace(oneMove);
			break;
		}
		i++;
		j++;
	}

	i = coor.x - 1;
	j = coor.y + 1;
	while (i >= 0 && j < 8) {
		if (!board->isEmpty(i, j)) {
			Coor oneMove = {i, j};
			attackRange.emplace(oneMove);
			break;
		}
		i--;
		j++;
	}

	i = coor.x + 1;
	j = coor.y - 1;
	while (i < 8 && j >= 0) {
		if (!board->isEmpty(i, j)) {
			Coor oneMove = {i, j};
			attackRange.emplace(oneMove);
			break;
		}
		i++;
		j--;
	}

	i = coor.x - 1;
	j = coor.y - 1;
	while (i >= 0 && j >= 0) {
		if (!board->isEmpty(i, j)) {
			Coor oneMove = {i, j};
			attackRange.emplace(oneMove);
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

	int i, j;

	i = coor.x + 1;
	j = coor.y + 1;
	while (i < 8 && j < 8) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		attackRange.emplace(oneMove);

		i++;
		j++;
	}

	i = coor.x - 1;
	j = coor.y + 1;
	while (i >= 0 && j < 8) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		attackRange.emplace(oneMove);

		i--;
		j++;
	}

	i = coor.x + 1;
	j = coor.y - 1;
	while (i < 8 && j >= 0) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		attackRange.emplace(oneMove);

		i++;
		j--;
	}

	i = coor.x - 1;
	j = coor.y - 1;
	while (i >= 0 && j >= 0) {
		if (!board->isEmpty(i, j)) break;
		Coor oneMove = {i, j};
		attackRange.emplace(oneMove);

		i--;
		j--;
	}

	return moveRange;
}

char Queen::getType() {
	return type;
}
