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

// builds dictionary with hardcoded name
void buildDict(vector<string> &, const char*);
bool searchForWord(vector<string> &, string&);

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
		// dictionary variables
		const char dictFileName[] = "diction10k.txt";		// path of dictionary 
		vector<string> dictVector;		// declare vector for dictionary
		buildDict(dictVector, dictFileName);	// populates vector with dictionary entries
		int lines = 0;		// holds num of strings in input file
		string test = "zulus";
		if (searchForWord(dictVector, test))
			cout << test << " was found!" << endl;
		else
			cout << test << " was not found!" << endl;
		string curLine;
		inFile >> lines;
		inFile.ignore(5, '\n');
		cout << lines << endl;
		for (int i = 0; i < lines; i++) {
			getline(inFile, curLine);
			cout << "phrase number: " << (i + 1) << endl << curLine << endl << endl;

		}
	}

	inFile.close();
	return 0;
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
		cout << "first dict value: " << dictVec[0] << " last dict value: " << dictVec[size] << endl;
		cout << "Dictionary sucessfully loaded!" << endl;
		dictFile.close();
	}
	return;	
}
