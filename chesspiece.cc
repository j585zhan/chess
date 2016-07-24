#include "chesspiece.h"

ChessPiece::ChessPiece(int color, Coor coor, Board *b):color {color}, coor {coor}, board{b}{}

int ChessPiece::getColor() {
	return color;
}

Coor ChessPiece::getCoor() {
	return coor;
}

ChessPiece::~ChessPiece() {}

