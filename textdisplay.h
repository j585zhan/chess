#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "view.h"
#include <vector>

class TextDisplay: public View {
public:
	TextDisplay();
	~TextDisplay();
	void print() override;
};

#endif
