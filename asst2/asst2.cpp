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
	
	//int longestPath = 0, numLongestPaths = 0;
	// create 2 values for the column numbers of longest row path and count 
	int priorLP = nodes, priorLPCount = nodes + 1;
	for(int x = 0; x < nodes; x++) {
		int longestInRow = 0;
		for(int y = 0; y < nodes; y++) {
			//if (x > 0)
			//	adjMatrix[x][priorLPCount] += adjMatrix[x - 1][priorLPCount];
			// continue loop if no relevant value/connection
			if (adjMatrix[x][y] == 0)
				continue;
			
			/* 
			if (adjMatrix[x][y] >= longestInRow) {
				if (longestInRow == adjMatrix[x][y])
					adjMatrix[x][priorLPCount] += 1;
				else
					adjMatrix[x][priorLPCount] = 1;
				cout << "row/col: " << x << " " << y << " length: " << adjMatrix[x][y] << " priorLPCount: " << adjMatrix[x][priorLPCount] << endl;
				longestInRow = adjMatrix[x][y];
				// check if pointed-to node has greater longest path and current node and priors
				//if (longestInRow == adjMatrix[x][y])
				//	longestPathCount += 1;
				//cout << "row/col: " << x << " " << y << " LPCount: " << longestPathCount << endl;
				// get edge length to given column(node pointed to)
				//longestInRow = adjMatrix[x][y];
				if ((longestInRow + adjMatrix[x][priorLP]) > adjMatrix[y][priorLP]) {
					adjMatrix[y][priorLP] = longestInRow + adjMatrix[x][priorLP];
					adjMatrix[y][priorLPCount] += adjMatrix[x][priorLPCount];
				}
				//if (y == (nodes - 1)) 
				//	adjMatrix[nodes - 1][priorLPCount] += adjMatrix[x][priorLPCount];
			
			}
			*/
			if ((adjMatrix[x][y] + adjMatrix[x][priorLP]) > adjMatrix[y][priorLP]) {
				adjMatrix[y][priorLP] = adjMatrix[x][y] + adjMatrix[x][priorLP];
				//adjMatrix[y][priorLPCount] += adjMatrix[x][priorLPCount];
			}
			f (adjMatrix[x][y] > longestInRow)
				longestInRow = adjMatrix[x][y];
			if (longestInRow == adjMatrix[x][y])
				adjMatrix[x][priorLPCount] += 1;
			
			cout << "row/col: " << x << " " << y << " length: " << adjMatrix[x][y] << " priorLPCount: " << adjMatrix[x][priorLPCount] << endl;
		}
	}
	cout << endl <<"Longest Path: " << adjMatrix[nodes - 1][priorLP] << endl << "Number of Longest Paths: " << adjMatrix[nodes - 1][priorLPCount] << endl;
	
	for(size_t i = 0; i < nodes - 1; ++i) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
	return 0;
}
