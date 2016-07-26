#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <memory>
#include <board.h>

struct Coor;

class Controller {
	std::shared_ptr<Board> board;
	bool presetBoard;
	
	bool validPlayer(const std::string &player);
	bool validPiece(const std::string &piece);
	bool validPos(const std::string &pos);
	Coor toCoor(const std::string &pos);
	void printTurn(bool isWhite);
	void setup(std::istream &is, bool showStep);
	void game();
	std::string getPromotion();
	
public:
	Controller();
	~Controller();
	void play();
};

#endif
