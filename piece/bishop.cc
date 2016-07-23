#include "bishop.h"
#include <string>
#include <vector>

using namespace std;

Bishop::Bishop(int color, Coor coor, Board *b): color {color}, coor {coor}, b{b}{
	type = "B";
}

Bishop::~Bishop(){}

void Bishop::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> Bishop::getAttackRange() {
	vector<Coor>attackRange;
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

vector<Coor> Bishop::getMoveRange() {
	vector<Coor>moveRange;
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

string Bishop::getType() {
	return type;
}
