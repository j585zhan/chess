#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include <iostream>
#include "controller.h"

class Controller {
	Board *board;
	View *view;
public:
	Controller();
	~Controller();

	void play();
	void game();
	void notify();
	std::string getPromotion();
	void setup();
	bool isCheck();
	bool isCheckmate();
};

#endif
