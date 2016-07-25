#include "unicodedisplay.h"
#include <iostream>


using namespace std;

UnicodeDisplay::UnicodeDisplay(): View() {
	unicodeSymbol['_'] = "\u25A1 ";
	unicodeSymbol[' '] = "\u25A0 ";

	unicodeSymbol['b'] = "\u2654 ";
	unicodeSymbol['q'] = "\u2655 ";
	unicodeSymbol['r'] = "\u2656 ";
	unicodeSymbol['b'] = "\u2657 ";
	unicodeSymbol['n'] = "\u2658 ";
	unicodeSymbol['p'] = "\u2659 ";

	unicodeSymbol['K'] = "\u265A ";
	unicodeSymbol['Q'] = "\u265B ";
	unicodeSymbol['R'] = "\u265C ";
	unicodeSymbol['B'] = "\u265D ";
	unicodeSymbol['N'] = "\u265E ";
	unicodeSymbol['P'] = "\u265F ";
}

UnicodeDisplay::~UnicodeDisplay() {}

void UnicodeDisplay::print() {
	for (int i = size - 1; i >= 0; --i) {
		cout << i + 1<< ' ';
		for (int j = 0; j < size; ++j) {
			cout << unicodeSymbol[theDisplay[j][i]];
		}
		cout << endl;
	}
	cout << endl << "  " << "abcdefgh" << endl << endl;
}
