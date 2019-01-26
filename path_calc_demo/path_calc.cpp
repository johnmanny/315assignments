/*
	Author: John Nemeth
	Description: finding number of longest paths and longest path value from standard input
	Sources: class material, previous projects
		 stackoverflow.com/questions/11535384/c-2-dimensional-array-with-variable-size-rows (for variable multi-dim arrays)
*/
#include <iostream>

using namespace std;

int main() {
	// spacesnum is distance between each value from input
	const int SPACESNUM = 1;
	int nodes = 0, edges = 0;

	// take first line of input
	cin >> nodes;
	cin.ignore(SPACESNUM, ' ');
	cin >> edges;
	cin.ignore(SPACESNUM, '\n');

	// create dynamic 2d array to use variable dimensions
	int** adjMatrix;
	adjMatrix = new int*[nodes];
	for(size_t i = 0; i < nodes; ++i) {
		//// created 2 extra columns
		// nodes + 1: longest path to that point
		// nodes + 2: longest path count of prior node
		adjMatrix[i] = new int[nodes + 2];
	}

	// init dynamic array values to zero to prevent memory errors
	int row = 0, column = 0, distValue = 0;	
	for(row = 0; row < nodes; row++){
		for(column = 0; column < nodes + 2; column++) {
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
	}

	// create 2 values extra columns for longestpath to row and longestpath count to row
	int priorLP = nodes, priorLPCount = nodes + 1;

	// init LPcount for first node
	adjMatrix[0][priorLPCount] = 1;

	//// using adjacency matrix
	// outside loop for rows (nodes)
	for(int x = 0; x < nodes; x++) {
		// inside loop for columns
		for(int y = 0; y < nodes; y++) {
			// if no connection to node, move to next column
			if (adjMatrix[x][y] == 0)
				continue;
			// if connection to next node is a longest path
			if ((adjMatrix[x][y] + adjMatrix[x][priorLP]) >= adjMatrix[y][priorLP]) {
				//// if next node's path is longest, add path counts together
				// otherwise set next longest count to current node's
				if ((adjMatrix[x][y] + adjMatrix[x][priorLP]) == adjMatrix[y][priorLP])
					adjMatrix[y][priorLPCount] += adjMatrix[x][priorLPCount];
				else
					adjMatrix[y][priorLPCount] = adjMatrix[x][priorLPCount];
				// set next node's longest path count
				adjMatrix[y][priorLP] = adjMatrix[x][y] + adjMatrix[x][priorLP];
			}
		}
	}

	cout << "longest path: " << adjMatrix[nodes - 1][priorLP] << endl << "number of longest paths: " << adjMatrix[nodes - 1][priorLPCount] << endl;
	
	// delete dynamic array to prevent memory leaks
	for(size_t i = 0; i < nodes; ++i) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;

	return 0;
}
