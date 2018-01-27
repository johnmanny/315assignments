/*
	Author: John Nemeth
	Description: finding number of longest paths and longest path value from standard input
	Sources: class material, previous projects
		 stackoverflow.com/questions/11535384/c-2-dimensional-array-with-variable-size-rows (for variable multi-dim arrays)
*/
#include <iostream>

using namespace std;

/*
struct node 
{
	int pathDist = 0;
	int longestPathTo = 0;
	int numOfLongest = 0;
};
*/

int main() {
	// spacesnum is distance between each value from input
	const int SPACESNUM = 1;
	int nodes = 0, edges = 0;
	
	cin >> nodes;
	cin.ignore(SPACESNUM, ' ');
	cin >> edges;
	cin.ignore(SPACESNUM, '\n');
	cout << nodes << ' ' << edges << endl;
	
	//int adjMatrix[nodes][nodes] = { 0 };
	int** adjMatrix = new int*[nodes];
	for(size_t i = 0; i < nodes; ++i) {
		// created 2 extra columns that tracks paths to node and count of longest paths
		adjMatrix[i] = new int[nodes + 2];
	}

	int row = 0, column = 0, distValue = 0;	
	for(int i = 0; i < edges; i++) {
		cin >> row;
		cin.ignore(SPACESNUM, ' ');
		cin >> column;
		cin.ignore(SPACESNUM, ' ');
		cin >> distValue;
		cin.ignore(SPACESNUM, '\n');
		adjMatrix[row - 1][column - 1] = distValue;
		cout << adjMatrix[row - 1][column - 1] << endl;
	}
	adjMatrix[0][5] = 282;
	adjMatrix[0][6] = 282;
	adjMatrix[2][6] = 282;
	cout << "row 1 col 6: " << adjMatrix[0][5] << endl;
	cout << "row 1 col 7: " << adjMatrix[0][6] << endl;
	
	int longestPath = 0, numLongestPaths = 0;
	for(int x = 0; x <= nodes - 1; x++) {
		for(int y = 0; y <= nodes - 1; y++) {
			//int longestInRow = 0, longestRowCount = 0;
			if (longestInRow <= adjMatrix[x][y]) {
				if (longestInRow == adjMatrix[x][y])
					longestRowCount++;
				else {
					longestInRow = adjMatrix[x][y];
					longestRowCount = 1;
				}
			}
			
			if (y == nodes - 1) {
				if (adjMatrix[x][y] > longestPath) 
					longestPath = adjMatrix[x][y];
			}
			
			if (adjMatrix[x][y] > longestInRow) {
				longestInRow = adjMatrix[x][y];
				longestRowCount += 1;
			} 
		}
		//numLongestPaths += longestRowCount;
		//longestInRow = 0;
		//longestRowCount = 0;
	}
	cout << endl <<"Longest Path: " << longestPath << endl << " Number of Longest Paths: " << numLongestPaths << endl;
	
	for(size_t i = 0; i < nodes - 1; ++i) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
	return 0;
}
