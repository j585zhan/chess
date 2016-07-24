#include "controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "board.h"
#include "view.h"
#include "textdisplay.h"

using namespace std;

Controller::Controller() {
	view = make_shared<TextDisplay>(); //same as above
	board = make_shared<Board>(view); //need to supply parameter for constrution of Board
}

Controller::~Controller() {}

bool Controller::validPlayer(const string &player) {
	if (player == "human") return true;
	else if (player == "computer1") return true;
	else if (player == "computer2") return true;
	else if (player == "computer3") return true;
	else if (player == "computer4") return true;
	else return false;
}

//kqbrnp

bool Controller::validPiece(const string &piece) {
	string s;
	s += toupper(piece[0]);
	if (s == "K" || s == "Q" || s == "B" || s == "R" || s == "N" || s == "P") {
		return true;
	}
	return false;
}

bool Controller::validPos(const string &pos) {
	if (pos.size() != 2) return false;
	if (pos[0] >= 'a' && pos[0] <= 'h') {
		if (pos[1] >= '1' && pos[1] <= '8') {
			return true;
		}
		return false;
	}
	return false;
}

Coor Controller::toCoor(const string &pos) {
	int x = pos[0] - 'a';
	int y = pos[1] - '1';
	Coor c {x, y};
	return c;
}

void Controller::notifyView(const char piece, const Coor c) {
	view->notify(piece, c);
}

void Controller::setup(istream &is) {
	// if (board) board->clearBoard();
	board->initBoard();
	view->print();
	string cmd;
	while (is >> cmd) {
		if (cmd == "+") {
			string piece, pos;
			is >> piece >> pos;
			if (validPiece(piece) && validPos(pos)) {
				Coor c = toCoor(pos);
				board->placePiece(piece[0], c);
				notifyView(piece[0], c); // notifyView() will place piece at pos 
				view->print();
			} else {
				cout << "Invalid + usage" << endl;
			}
		} else if (cmd == "-") {
			string pos;
			is >> pos;
			if (validPos(pos)) {
				Coor c = toCoor(pos);
				board->removePiece(c);
				char emptyPosColor;
				if (c.x % 2 == 0) {
					if (c.y % 2 == 0) emptyPosColor = '_';
					else emptyPosColor = ' ';
				} else {
					if (c.y % 2 == 0) emptyPosColor = ' ';
					else emptyPosColor = '_';
				}
				notifyView(emptyPosColor, c);
				view->print();
			} else {
				cout << "Invalid - usage, check your coordinates" << endl;
			}
		} else if (cmd == "=") {
			string color;
			is >> color;
			if (color == "black"){
				board->wturn = false;
			} else if (color == "white") {
				board->wturn = true;
			} else {
				cout << "Invalid color" << endl;
			}
		} else if (cmd == "done") {
			if (board->validBoard()) {
				cout << "Board setup completed" << endl;
				break;
			} else {
				cout << "Invalid Board, please double check" << endl;
			}
		}
	}
}

void Controller::game() {
	board->initBoard();
	view->print();
	string cmd;
	while (cin >> cmd) {
		if (board->isCheckmate()) {
			int result = board->resign(); //0 means white resign, 1 means black resign
			if (result) {
				cout << "Checkmate! White wins!" << endl;
			} else {
				cout << "Checkmate! Black wins!" << endl;
			}
			break;
		}
		if (board->isCheck()) {
			if (board->wturn) {
				cout << "White is in check" << endl;
			} else {
				cout << "Black is in check" << endl;
			}
		}
		if (board->isStalemate()) {
			cout << "Stalemate!" << endl;
			break;
		}
		if (cmd == "move") {
			string start, dest;
			cin >> start >> dest;
			if (validPos(start) && validPos(dest)) {
				string result = board->makeMove(toCoor(start), toCoor(dest));
				if (result == "empty") {
					cout << "No valid piece at chosen position" << endl;
					continue;
				} else if (result == "invalid") {
					cout << "Invalid move" << endl;
					continue;
				}
				view->print();
			} else {
				cout << "Incorrect usage of move, check your coordinates again" << endl;
			}
		} else if (cmd == "resign") {
			if (board->wturn) {
				cout << "Black wins!" << endl;
			} else {
				cout << "White wins!" << endl;
			}
		} else if (cmd == "undo") {
			// place implemation of undo here
		}
	}
	cout << "Final Score:" << endl;
	cout << "White: " << board->getWscore() << endl;
	cout << "Black: " << board->getBscore() << endl;
}

void Controller::play() {
	string cmd;
	while (cin >> cmd) {
		if (cmd == "game") {
			string player1, player2;
			cin >> player1 >> player2;
			if (validPlayer(player1) && validPlayer(player2)) {
				board->setPlayer(player1, player2);
				game();
			}
		} else if (cmd == "setup") {
			setup(cin);
		} else if (cmd == "read") {
			string filename;
			cin >> filename;
			ifstream ifs;
			ifs.open(filename);
			setup(ifs);
		}
	}
}
