#include "textdisplay.h"
#include <iostream>

using namespace std;

struct Coor {
	int x;
	int y;
};

const int size = 8;

TextDisplay::TextDisplay() {
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

TextDisplay::~TextDisplay() {}

void TextDisplay::notify(char piece, Coor coor) {
	theDisplay[coor.x][coor.y] = piece;
}

void TextDisplay::print() {
	for (int i = size - 1; i >= 0; --i) {
		cout << i + 1 << ' ';
		for (int j = 0; j < size; ++j) {
			cout << theDisplay[i][j];
		}
		cout << endl;
	}
	cout << endl << "  " << "abcdefgh" << endl;
}
