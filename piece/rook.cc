#include "rook.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Rook::Rook(int color, Coor coor, Board *b): ChessPiece(color, coor, b)  {
	type = 'R';
}

Rook::~Rook(){}

void Rook::makeMove(Coor dest) {
	coor = dest;
}

vector<Coor> Rook::getAttackRange() {
	vector<Coor>attackRange;
	for (int i = coor.x + 1; i < 8; i++) {
		if (!board->isEmpty(i, coor.y)) {
			if (board->getPos(Coor{i, coor.y})->getColor() != color) {
				Coor oneMove = {i, coor.y};
//				cout<<"R: "<<i<<coor.y<<endl;
				attackRange.emplace_back(oneMove);
			}
			break;
		}
	}

	for (int i = coor.x - 1; i >= 0; i--) {
		if (!board->isEmpty(i, coor.y)) {
			if (board->getPos(Coor{i, coor.y})->getColor() != color) {
				Coor oneMove = {i, coor.y};
//				cout<<"R: "<<i<<coor.y<<endl;
				attackRange.emplace_back(oneMove);
			}
			break;
		}
	}

	for (int i = coor.y + 1; i < 8; i++) {
		if (!board->isEmpty(coor.x, i)) {
			if (board->getPos(Coor{coor.x, i})->getColor() != color) {
				Coor oneMove = {coor.x, i};
//				cout<<"R: "<<i<<coor.y<<endl;
				attackRange.emplace_back(oneMove);
			}
			break;
		}
	}

	for (int i = coor.y - 1; i >= 0; i--) {
		if (!board->isEmpty(coor.x, i)) {
			if (board->getPos(Coor{coor.x, i})->getColor() != color) {
				Coor oneMove = {coor.x, i};
//				cout<<"R: "<<i<<coor.y<<endl;
				attackRange.emplace_back(oneMove);
			}
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

	return moveRange;
}

char Rook::getType() {
	return type;
}
