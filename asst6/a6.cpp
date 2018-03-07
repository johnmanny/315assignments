/*
	Author: John Nemeth
	Description:
	Sources:
*/

#include <iostream>
#include <string>
//#include <cstring>
#include <fstream>
#include <vector>
//#include <bits/stdc++.h>
using namespace std;

void buildDict(vector<string> &, const char*);	// passes hardocoded path
bool searchForWord(vector<string> &, string&);	// uses binary search
void checkValidSplit(string&);		// iterative, bottom-up approach

// main
int main(int argc, char* argv[]) {
	
	if (argc == 1)		// check for no file passed
		cerr << "Error! Usage is " << argv[0] << " 'filename'" << endl;
	// declare inputs
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile)		// check for file not opened
		cout << "Failed to open " << argv[1] << endl;
	else {
		// setup dictionary for words
		const char dictFileName[] = "diction10k.txt";		// path of dictionary 
		vector<string> dictVector;		// declare vector for dictionary
		buildDict(dictVector, dictFileName);	// populates vector with dictionary entries
		int lines = 0;		// holds num of strings in input file
		string test = "zulus";
		if (searchForWord(dictVector, test))
			cout << test << " was found!" << endl;
		else
			cout << test << " was not found!" << endl;
		// get input from problem files
		string curLine;
		inFile >> lines;
		inFile.ignore(5, '\n');
		cout << lines << endl;
		for (int i = 0; i < lines; i++) {
			getline(inFile, curLine, '\n');
			cout << "phrase number: " << (i + 1) << endl << curLine << endl << endl;
			checkValidSplit(curLine);
		}
	}

	inFile.close();
	return 0;
}

// check if word has valid break
void checkValidSplit(string& word) {
	int size = word.size();		// check for valid word size
	if (size == 0) 
		cout << "word size is zero. failed to find valid split" << endl;
	else {
		/* explanation: 
		array - created dynamic array(vector) holds the ending index of
			a word in it's index value. that respective value of the index
			is the starting position of a word within the string. if there is
			no word that starts at i in splitVec[i], splitVec[i] = -1. entries
			in the vector are inited to -1.
		subproblem- each time a position is evaluated, it needs to have an ending index
			for the split to be valid
		*/
		vector<int> splitVec(size, -1);
		//cout << splitVec[size] << endl;
		for (int i = size - 1; i >= 0; i--) {	// evaluates from last entry forward
			// check for word at from last element to index
			if (splitVec[i] == -1 && searchForWord(word.substr(i, size - i))) 
				splitVec[i + 1] = i;	// allow to move to second loop
			// check following index values to move up new word end
			if (splitVec[i] != -1) {
				// check for last element (then split is complete)
				if (i == 0) 
					// call the print function
				for (int j = i - 1; j > 0; j--) {
					if (splitVec[j] == -1 && searchForWord(word.substr(j, i - j)))
						splitVec[j] = j + (i - j);
					if (j == 1)	// if the last operation 
			} 
		}
	}
}

// to search for word in dictionary using iterative binary search
bool searchForWord(vector<string> &dictVec, string& word) {
	int size = dictVec.size();
	int leftEnd = 0, rightEnd = size, evalIndex = 0;
	int iteration = 0;
	while (leftEnd <= rightEnd) {
		evalIndex = leftEnd + (rightEnd - leftEnd) / 2;
		string indexVal = dictVec[evalIndex];
		cout << "indexVal is: " << indexVal << " on iteration " << iteration << endl;
		iteration++;
		if (word.compare(indexVal) == 0)
			return true;
		if (word.compare(indexVal) < 0)
			rightEnd = evalIndex - 1;
		else	// ignore right half of dict
			leftEnd = evalIndex + 1;
	}
	return false;
}


// to build dictionary
void buildDict(vector <string> &dictVec, const char* fileName) {
	ifstream dictFile;
	dictFile.open(fileName);
	if (!dictFile) {
		cout << "dictionary not found" << endl;
	}
	else {
		string dictLine;
		int index = 0;
		while (!dictFile.eof()) {
			getline(dictFile, dictLine, '\n');
			dictVec.push_back(dictLine);
			index++;
		}
		int size = dictVec.size();
		while (dictVec[size].compare("") == 0) {	// delete empty tail entries	
			dictVec.pop_back();
			size--;
		}
		cout << "1st dict val: " << dictVec[0] << " last dict val: " << dictVec[size] << endl;
		cout << "Dictionary sucessfully loaded!" << endl;
		dictFile.close();
	}
	return;	
}
