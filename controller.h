#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <memory>


class Board;
class View;
struct Coor;

class Controller {
	std::share_ptr<Board> board;
	std::share_ptr<View> view;
	void setup();
	void game(const std::string &player1, const std::string &player2);
	void notify();
	std::string getPromotion();
	bool validPlayer(const std::string &player);
	bool validPiece(const std::string &piece);
	bool validPos(const std::string &pos);
	Coor toCoor(const std::string &pos);
public:
	Controller();
	~Controller();
	void play();
};

#endif
