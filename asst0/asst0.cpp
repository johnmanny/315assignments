/*
	Author: John Nemeth
	Description: finding the sum and product of pairs of input values
	Sources: class material, previous projects
*/
#include <iostream>

using namespace std;

int main() {
	const int SPACESNUM = 1, DISTTONEWLINE = 1;
	int x, y, lines = 0;
	cin >> lines;
	cin.ignore(DISTTONEWLINE, '\n');
	
	while (lines != 0) {
		cin >> x;
		cin.ignore(SPACESNUM, ' ');
		cin >> y;
		cin.ignore(DISTTONEWLINE, '\n');
		
		cout << x + y << ' ' << x * y << endl;
		lines--;
	}

	return 0;
}
