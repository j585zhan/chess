#ifndef __VIEW_H__
#define __VIEW_H__

#include <vector>

struct Coor;

class View {
protected:
	std::vector<std::vector<char>> theDisplay;
	const int size = 8;
public:
	View();
	void notify(char piece, Coor coor);
	virtual ~View() = 0;
	virtual void print() = 0;
};

#endif
