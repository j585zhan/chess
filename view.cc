#include "view.h"
#include "board.h"
#include <vector>

using namespace std;

View::View() {
	theDisplay = vector<vector<char>>(size, vector<char>(size));
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (i % 2 == 0) {
				if (j % 2 == 0) theDisplay[i][j] = '_';
				else theDisplay[i][j] = ' ';
			} else {
				if (j % 2 == 0) theDisplay[i][j] = ' ';
				else theDisplay[i][j] = '_';
			}
		}
	}
}

View::~View() {}

void View::notify(char piece, Coor coor) {
	if (piece == 'E') {
		if (coor.x % 2 == 0) {
			if (coor.y % 2 == 0) piece = '_';
			else piece = ' ';
		} else {
			if (coor.y % 2 == 0) piece = ' ';
			else piece = '_';
		}
	} 
	theDisplay[coor.x][coor.y] = piece;
}
