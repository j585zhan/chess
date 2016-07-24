#include "textdisplay.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay(): View() {}

TextDisplay::~TextDisplay() {}

void TextDisplay::print() {
	for (int i = size - 1; i >= 0; --i) {
		cout << i + 1<< ' ';
		for (int j = 0; j < size; ++j) {
			cout << theDisplay[j][i];
		}
		cout << endl;
	}
	cout << endl << "  " << "abcdefgh" << endl << endl;
}
