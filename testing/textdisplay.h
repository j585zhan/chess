#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "view.h"
#include <vector>

struct Coor;

class TextDisplay: public View {
	std::vector<std::vector<char>> theDisplay;
public:
	TextDisplay();
	~TextDisplay();
	void notify(char piece, Coor coor) override;
	void print() override;
};

#endif
