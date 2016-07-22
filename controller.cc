#include "controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

Controller::Controller(): {
	board = share<Board>(); //need to supply parameter for constrution of Board
	view = make_share<View>(); //same as above
}

bool Controller::validPlayer(std::string player) {
	if (player == "human") return true;
	else if (player == "computer1") return true;
	else if (player == "computer2") return true;
	else if (player == "computer3") return true;
	else if (player == "computer4") return true;
	else return false;
}

void setup() {
	string cmd;
	while (cin >> cmd) {
		if (cmd == "+") {
			
		} else if (cmd == "-") {

		} else if (cmd == "=") {

		} else if (cmd == done) {

		}
	}
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
			setup();
		} else if (cmd == "read") {
			string filename;
			cin >> filename;
			ifstream ifs;
			ifs.open(filename);
			// need more, come back when i finish setup()
		}
	}
}

void Controller::game() {
	board->initBoard();
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
			if (board->wTurn) {
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
			string result = board->makeMove(start, dest);
			if (result == "empty") {
				cout << "No valid piece at chosen position" << endl;
				continue;
			} else if (result == "invalid") {
				cout << "Invalid move" << endl;
				continue;
			}
		} else if (cmd == "resign") {
			if (board->wTurn) {
				cout << "Black wins!" << endl;
			} else {
				cout << "White wins!" << endl;
			}
		} else if (cmd == "undo") {
			// place implemation of undo here
		}
	}
	cout << "Final Score:" << endl;
	cout << "White: " << board->getWScore() << endl;
	cout << "Black: " << board->getBScore() << endl;
}

Controller::~Controller() {}
