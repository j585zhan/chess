#include <iostream>
#include "view.h"
#include "textdisplay.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
	TextDisplay t;
	t.print();
	string s;
	vector <int> table;
	for (int i = 0; i < 64; ++i) table.emplace_back(i);
	srand(time(nullptr));
	random_shuffle(table.begin(), table.end());
	
	while (cin >> s) {
		int j = 0;
		for (auto i : table) { 
			cout << table.at(i) << endl;
			j++;
		}
		cout << "# printed is" << j << endl;
	}

	return 0;
}
