#include "controller.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "board.h"

using namespace std;

Controller::Controller(): presetBoard {false} {
	board = make_shared<Board>();
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


void Controller::setup(istream &is, bool showStep) {
	presetBoard = true;
	board->initBoard();
	board->clearBoard();
	if (showStep) board->print();
	string cmd;
	while (is >> cmd) {
		if (cmd == "+") {
			string piece, pos;
			is >> piece >> pos;
			if (validPiece(piece) && validPos(pos)) {
				Coor c = toCoor(pos);
				board->placePiece(piece[0], c);
				if (showStep) board->print();
			} else {
				cout << "Invalid + usage" << endl;
			}
		} else if (cmd == "-") {
			string pos;
			is >> pos;
			if (validPos(pos)) {
				Coor c = toCoor(pos);
				board->removePiece(c);
				if (showStep) board->print();
			} else {
				cout << "Invalid - usage, check your coordinates" << endl;
			}
		} else if (cmd == "=") {
			string color;
			is >> color;
			if (color == "black"){
				board->wturn = false;
				cout << "Black player will move first" << endl;
			} else if (color == "white") {
				board->wturn = true;
				cout << "White player will move first" << endl;
			} else {
				cout << "Invalid color" << endl;
			}
		} else if (cmd == "done") {
			if (board->validBoard()) {
				cout << "Board setup completed" << endl;
				board->saveHistory();
				break;
			} else {
				cout << "Invalid Board, please double check" << endl;
			}
		} else if (!cin.eof()) {
			cout << "Invalid setup command" << endl;
		}
	}
	if (!showStep) board->print();
}

void Controller::printTurn(bool isWhite) {
	if (isWhite) cout << "White player's turn" << endl;
	else cout << "Black player's turn" << endl;
}

void Controller::game() {
	if (!presetBoard) board->initBoard();
	board->print();
	printTurn(board->wturn);
	string cmd;
	while (cin >> cmd) {
		if (cmd == "move") {
			// check if it is AI
			if (board->wturn && board->aiW) {
				cout << board->aiW->makeMove() << endl;
				board->print();
			} else if (!board->wturn && board->aiB) {
				cout << board->aiB->makeMove() << endl;
				board->print();
			} else {
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
					board->print();
					if (board->needPromotion()) {
						string choice;
						char type;
						board->wturn = !board->wturn;
						cout << "Promote to rook, knight, bishop or queen?" << endl;
						while (cin >> choice) {
							if (choice == "rook") {
								if (board->wturn) type = 'R';
								else type = 'r';
								break;
							} else if (choice == "knight") {
								if (board->wturn) type = 'N';
								else type = 'n';
								break;
							} else if (choice == "bishop") 	{
								if (board->wturn) type = 'B';
								else type = 'b';
								break;
							} else if (choice == "queen") {
								if (board->wturn) type = 'Q';
								else type = 'q';
								break;
							} else if (!cin.eof()) {
								cout << "Invalid choice, type rook, knight, bishop or queen" << endl;
							}
						}
						board->placePiece(type, toCoor(dest));
						board->wturn = !board->wturn;
						board->print();
					}
					printTurn(board->wturn);
				} else {
					cout << "Incorrect usage of move, check your coordinates again" << endl;
				}
			}
			
		} else if (cmd == "resign") {
			if (!board->resign()) {
				cout << "Black wins!" << endl;
				return;
			} else {
				cout << "White wins!" << endl;
				return;
			}
		} else if (cmd == "undo") {
			board->undo(false);
			board->print();
		} else if (!cin.eof()) {
			cout << "Invalid move command" << endl;
		}
		if (board->isCheckmate()) {
			int result = board->resign(); //0 means white resign, 1 means black resign
			if (result) {
				cout << "Checkmate! White wins!" << endl;
			} else {
				cout << "Checkmate! Black wins!" << endl;
			}
			break;
		}
		if (board->isStalemate()) {
			cout << "Stalemate!" << endl;
			break;
		}
		if (board->isCheck()) {
			if (board->wturn) {
				cout << "White is in check" << endl;
			} else {
				cout << "Black is in check" << endl;
			}
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
				presetBoard = false;
			}
		} else if (cmd == "setup") {
			setup(cin, true);
		} else if (cmd == "read") {
			string filename;
			cin >> filename;
			ifstream ifs;
			ifs.open(filename);
			setup(ifs, false);
		} else if (!cin.eof()) {
			cout << "Invalid game command" << endl;
		}
	}
	cout << "Final Score:" << endl;
	cout << "White: " << board->getWscore() << endl;
	cout << "Black: " << board->getBscore() << endl;
}
