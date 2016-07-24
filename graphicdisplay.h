#ifndef __GRAPHDISPLAY_H__
#define __GRAPHDISPLAY_H__

#include "view.h"
#include <vector>

struct Coor;

class GraphicDisplay: public View {
	std::vector<std::vector<char>> theDisplay;
public:
	TextDisplay();
	~TextDisplay();
	void notify(char piece, Coor coor) override;
	void print() override;
};

#endif
