#ifndef __UNICODEDISPLAY_H__
#define __UNICODEDISPLAY_H__

#include "view.h"
#include <vector>
#include <map>
#include <string>

class UnicodeDisplay: public View {
	std::map<char, std::string> unicodeSymbol;
public:
	UnicodeDisplay();
	~UnicodeDisplay();
	void print() override;
};

#endif
