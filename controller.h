#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <memory>

class Board;
class View;
struct Coor;

class Controller {
	std::shared_ptr<Board> board;
	// std::shared_ptr<View> view;
	
	bool validPlayer(const std::string &player);
	bool validPiece(const std::string &piece);
	bool validPos(const std::string &pos);
	Coor toCoor(const std::string &pos);
	void setup(std::istream &is);
	void game();
	std::string getPromotion();
public:
	Controller();
	~Controller();
	void play();
	// void notifyView(const char piece, const Coor c);
};

#endif
