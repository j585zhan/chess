#include "graphicdisplay.h"
#include <iostream>

using namespace std;

GraphicDisplay::GraphicDisplay(): View() {}

GraphicDisplay::~GraphicDisplay() {}

void GraphicDisplay::print() {
	// first draw the Board
	for (int i = 0; i < size; ++i) {
		for (int j = size - 1; j >= 0; --j) {
			if (i % 2 == j % 2) 
				w.fillRectangle(i * 100, j * 100, 100, 100, Xwindow::White);
			else 
				w.fillRectangle(i * 100, j * 100, 100, 100, Xwindow::Black);
		}
	}
	// The draw the pieces
	for (int i = 0; i < size; ++i) {
		for (int j = size - 1; j >= 0; --j) {
			if (theDisplay[i][j] == ' ' || theDisplay[i][j] == '_') continue;
			w.drawString(i * 100 + 50, 750 - j * 100, string(1, theDisplay[i][j]), Xwindow::Orange);
		}
	}
}
