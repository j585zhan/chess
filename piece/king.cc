#include "king.h"
#include <string>
#include <vector>
#include <iostream>

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
	if (coor.x + 1 < 8 && !board->isEmpty(coor.x + 1, coor.y)
		&& board->getPos(Coor{coor.x + 1, coor.y})->getColor() != color) {
		Coor oneMove = {coor.x + 1, coor.y};
		attackRange.emplace_back(oneMove);
	}
	if (coor.x - 1 >= 0 && !board->isEmpty(coor.x - 1, coor.y)
		&& board->getPos(Coor{coor.x - 1, coor.y})->getColor() != color) {
		Coor oneMove = {coor.x - 1, coor.y};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y + 1 < 8 && !board->isEmpty(coor.x, coor.y + 1)
		&& board->getPos(Coor{coor.x, coor.y + 1})->getColor() != color) {
		Coor oneMove = {coor.x, coor.y + 1};
		attackRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && !board->isEmpty(coor.x, coor.y - 1)
		&& board->getPos(Coor{coor.x, coor.y - 1})->getColor() != color) {
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
	if (coor.y + 1 < 8 && coor.x + 1 < 8 && board->isEmpty(coor.x + 1, coor.y + 1)) {
		Coor oneMove = {coor.x + 1, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 1 < 8 && coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y + 1)) {
		Coor oneMove = {coor.x - 1, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.x + 1 < 8 && board->isEmpty(coor.x + 1, coor.y)) {
		Coor oneMove = {coor.x + 1, coor.y};
		moveRange.emplace_back(oneMove);
	}
	if (coor.x - 1 >= 0 && board->isEmpty(coor.x - 1, coor.y)) {
		Coor oneMove = {coor.x - 1, coor.y};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y + 1 < 8 && board->isEmpty(coor.x, coor.y + 1)) {
		Coor oneMove = {coor.x, coor.y + 1};
		moveRange.emplace_back(oneMove);
	}
	if (coor.y - 1 >= 0 && board->isEmpty(coor.x, coor.y - 1)) {
		Coor oneMove = {coor.x, coor.y - 1};
		moveRange.emplace_back(oneMove);
	}
	
	//casting
		//un move
	if (!board->isMove(coor) && coor.x+3 < 8 && !board->isMove(Coor{coor.x + 3, coor.y})) {
		//have gap
		if (board->isEmpty(coor.x + 2, coor.y) &&
			board->isEmpty(coor.x + 1, coor.y)) {
			Coor oneMove = {coor.x + 2, coor.y};
			moveRange.emplace_back(oneMove);
		}
	}

	if (!board->isMove(coor) && coor.x-4 >= 0 && !board->isMove(Coor{coor.x - 4, coor.y})) {
		//have gap
		if (board->isEmpty(coor.x - 3, coor.y) &&
			board->isEmpty(coor.x - 2, coor.y) &&
			board->isEmpty(coor.x - 1, coor.y)) {
			Coor oneMove = {coor.x - 2, coor.y};
			moveRange.emplace_back(oneMove);
		}
	}
	return moveRange;
}

char King::getType() {
	return type;
}
