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
	
	bool validPlayer(const std::string &player);
	bool validPiece(const std::string &piece);
	bool validPos(const std::string &pos);
	Coor toCoor(const std::string &pos);
	void setup(istream &is);
	void game(const std::string &player1, const std::string &player2);
	std::string getPromotion();
public:
	Controller();
	~Controller();
	void play();
};

#endif
