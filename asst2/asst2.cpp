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
	
	int** adjMatrix;
	adjMatrix = new int*[nodes];
	for(size_t i = 0; i < nodes; ++i) {
		//// created 3 extra columns
		// nodes + 1: longest path to that point
		// nodes + 2: longest path count
		// nodes + 3: longestpath value in row
		adjMatrix[i] = new int[nodes + 3];
	}
	
	// init dynamic array values
	int row = 0, column = 0, distValue = 0;	
	for(row = 0; row < nodes; row++){
		for(column = 0; column < nodes + 3; column++) {
			adjMatrix[row][column] = 0;
		}
	}
	
	// assign edge values in matrix
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
	int priorLP = nodes, priorLPCount = nodes + 1, longestPRowVal = nodes + 2;
	int longestPath = 0, longestInRow = 0;
	bool firstInRow = true;
	//adjMatrix[0][priorLPCount] = 1;
	for(int x = 0; x < nodes; x++) {
		longestInRow = 0;
		firstInRow = true;
		for(int y = 0; y < nodes; y++) {
			//if (x > 0)
			//	adjMatrix[x][priorLPCount] += adjMatrix[x - 1][priorLPCount];
			// continue loop if no relevant value/connection

			/*if (x > y) {
				if ((adjMatrix[y][x] + adjMatrix[y][priorLP]) == longestPath) {
					cout << "--LRCOUNTCHECK" << endl;
					cout << "checking row/col: " << y << ' ' << x;
					cout << " is " << adjMatrix[y][x] << endl;
					cout << " -- adding pathval: " << adjMatrix[y][longestPRowVal];
					cout << " and count " << adjMatrix[y][priorLPCount];
					cout << " to rowcount: " << adjMatrix[x][priorLPCount];
					//adjMatrix[x][priorLPCount] += adjMatrix[y][priorLPCount];
					adjMatrix[x][priorLPCount] = adjMatrix[y][priorLPCount];
					cout << " equals: " << adjMatrix[x][priorLPCount] << endl;
				}
			}*/
			//if (y == (nodes - 1))
			//	LPRCount = adjMatrix[x][priorLPCount];
			
			if (adjMatrix[x][y] == 0)
				continue;
			
			/*
			if (longestInRow == adjMatrix[x][y])
				adjMatrix[x][priorLPCount] += 1;
			if (adjMatrix[x][y] > longestInRow) {
				//if (longestInRow == 0)
				adjMatrix[x][priorLPCount] = LPRCount;
				//else
				//	adjMatrix[x][priorLPCount] = LPNum;
				longestInRow = adjMatrix[x][y];
				adjMatrix[x][longestPRowVal] = longestInRow;
			}
			*/
			//if ((longestPath + adjMatrix
			/*(if (longestInRow == adjMatrix[x][y]) {
				adjMatrix[x][priorLPCount] += 1;
				cout << "CHECK IT BRHRHRHRHRHRHRHRHHRHRHRHRH" << endl;
			}
			if ((longestInRow < adjMatrix[x][y]) && firstInRow) {
				firstInRow = false;
				longestInRow = adjMatrix[x][y];
				adjMatrix[x][priorLPCount] = 1;
			}
			if (longestInRow < adjMatrix[x][y])
				adjMatrix[x][priorLPCount] = 1;
			*/
			if ((adjMatrix[x][y] + adjMatrix[x][priorLP]) >= adjMatrix[y][priorLP]) {
				adjMatrix[y][priorLP] = adjMatrix[x][y] + adjMatrix[x][priorLP];
				longestPath = adjMatrix[y][priorLP];
				adjMatrix[y][priorLPCount] = adjMatrix[x][priorLPCount] + 1;
				cout << "sent: " << adjMatrix[x][priorLPCount] << " from row: " << x << " to row: ";
				cout << y << " and it's now: " << adjMatrix[y][priorLPCount] << endl;
			}
			//if (longestPath == (adjMatrix[x][y] + adjMatrix[x][priorLP]))
				
			//if (longestPath == adjMatrix[x][y])
			//	adjMatrix[x][priorLPCount] += 1;
			
			
			cout << "row/col: " << x << " " << y << " length: " << adjMatrix[x][y];
			cout << " priorLPCount: " << adjMatrix[x][priorLPCount];
			cout << " highestRowVal: " << adjMatrix[x][longestPRowVal] << endl;
		}
	}
	//adjMatrix[nodes - 1][priorLP] = 5;
	//adjMatrix[nodes - 1][priorLPCount] = 10;
	//cout << "longest path: " << adjMatrix[nodes - 1][priorLP] << endl << "number of longest paths: " << adjMatrix[nodes - 1][priorLPCount] << endl;
	cout << "longest path: " << adjMatrix[nodes - 1][priorLP] << endl << "number of longest paths: " << adjMatrix[nodes - 1][priorLPCount] << endl;
	for(size_t i = 0; i < nodes; ++i) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
	return 0;
}
