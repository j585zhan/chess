#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__

#include "view.h"
#include <vector>
#include "xwindow/window.h"

class GraphicDisplay: public View {
	Xwindow w;
public:
	GraphicDisplay();
	~GraphicDisplay();
	void print() override;
};

#endif
