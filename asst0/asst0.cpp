/*
	Author: John Nemeth
	Description: todo
	Sources: todo
*/
#include <iostream>
#include <string>

using namespace std;

int main() {
	const int SPACESNUM = 1, DISTTONEWLINE = 1, FIRSTLINE = 3;
	int x, y = 0;
	cin.ignore(FIRSTLINE, '\n');
	while (cin) {
		cin >> x;
		cin.ignore(SPACESNUM, ' ');
		cin >> y;
		cin.ignore(DISTTONEWLINE, '\n');
		
		cout << x << ' ' << y << endl;
	}


	return 0;
}
