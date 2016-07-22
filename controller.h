#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include <memory>

class Controller {
	std::share_ptr<Board> board;
	std::share_ptr<View> view;
	bool validPlayer(std::string player);
	void setup();
	void game(std::string player1, std::string player2);
	void notify();
	std::string getPromotion();
public:
	Controller();
	~Controller();
	void play();
};

#endif
