/*
	Author: John Nemeth
	Description: populates vector with words from dictionary file, takes specified input file
			with strings to determine whether entire string can be split with spaces
			to form words found in dictionary file.
	Sources: geeks4geeks word break examples, class material
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

bool buildDict(vector<string> &, const char*);		// passes hardocoded path
bool searchForWord(vector<string> &, string&);		// uses binary search
void checkValidSplit(vector<string> &, string&);	// iterative, bottom-up approach
void printSplitWord(vector<int> &, string&);		// print a valid split word

// main
int main(int argc, char* argv[]) {
	ifstream inFile;		// declare input stream for string file
	inFile.open(argv[1]);
	if (argc == 1)			// check for no file passed
		cerr << "Error! Usage is " << argv[0] << " 'filename'" << endl;
	else if (!inFile)		// check for file not opened
		cout << "Failed to open " << argv[1] << endl;
	else {
		// setup dictionary for words
		const char dictFileName[] = "diction10k.txt";			// path of dictionary 
		vector<string> dictVector;					// declare vector(dynamic array) for dictionary
		if (buildDict(dictVector, dictFileName))			// populates vector with dictionary entries, checks for errors
			cout << "--------No errors loading dictionary!\n" << endl;
		else {
			cout << "--------Error building dictionary from '" << dictFileName << "'! Exiting...\n" << endl;	
			return 0;
		}
		int lines = 0;					// holds number of strings in input file
		string curLine;
		inFile >> lines;
		inFile.ignore(5, '\n');
		for (int i = 0; i < lines; i++) {		// loops through each given string from the input file
			getline(inFile, curLine, '\n');
			cout << "\tphrase number: " << (i + 1) << "\n\t" << curLine << endl << endl;
			checkValidSplit(dictVector, curLine);		// call for checking split
		}
	}
	inFile.close();
	return 0;
}

// to build dictionary
bool buildDict(vector <string> &dictVec, const char* fileName) {
	ifstream dictFile;		// declare new input stream
	dictFile.open(fileName);
	if (!dictFile) {		// error checking for no dictfile in directory
		cout << "dictionary '" << fileName << "' not found" << endl;
		return false;
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
		dictFile.close();
	}
	return true;	
}

// uses binary search on the built dictionary to find given word if present
bool searchForWord(vector<string> &dictVec, string& word) {
	int size = dictVec.size();
	int leftEnd = 0, rightEnd = size, evalIndex = 0;
	while (leftEnd <= rightEnd) {
		evalIndex = leftEnd + (rightEnd - leftEnd) / 2;		// calculation for successive middle index
		string indexVal = dictVec[evalIndex];
		if (word.compare(indexVal) == 0)	// words are equal
			return true;
		if (word.compare(indexVal) < 0)		// ignore left half of dict
			rightEnd = evalIndex - 1;
		else					// ignore right half of dict
			leftEnd = evalIndex + 1;
	}
	return false;
}

// if valid word split found, checkValidSplit passes vector and word string to print, otherwise prints failure
void checkValidSplit(vector<string> &dictVec, string& word) {
	int size = word.size();		// check for valid word size
	if (size == 0) 
		cout << "word size is zero. failed to find valid split\n" << endl;
	else {
		int length = 0;
		string subString;
		vector<int> splitVec(size, -1);		// declare vector with size and initialize entries to -1
		for (int i = size; i >= 0; i--) {	// evaluates bottom-up, i always beginning of possible word
			length = size - (i - 1);	// set length of word evaluated
			subString = word.substr(i, length);	// possible word starts at i, ends at next evaluated word (i + length)
			if ((splitVec[i] == -1) && (searchForWord(dictVec, subString))) 	// if doesn't have word already and in dict
				splitVec[i] = i + length;	// set end of word that starts at i in splitword vector
			if (splitVec[i] != -1) {		// if word starts at that index
				if (i == 0) {			// split is complete if reached first element
					printSplitWord(splitVec, word);		// print completed string partition
					return;
				}
				for (int j = i - 1; j >= 0; j--) {		// j always beginning of possible word
					subString = word.substr(j, i - j);	// length of new word always end - start
					if (splitVec[j] == -1 && searchForWord(dictVec, subString))
						splitVec[j] = i - j;		// set length of new word that starts at j
					if ((j == 0) && (splitVec[j] != -1)) {	// split is complete if first element has word start
						printSplitWord(splitVec, word);
						return;
					}
				} 
			}
		}
	}
	cout << "\titerative attempt:\n\tNO, can't be split\n--------------------------------------------------------------\n";
	return;
}

// prints successive words
void printSplitWord(vector<int> &splitVec, string& curWord) {
	int wordIndex = 0, wordSize = curWord.size();
	cout << "\titerative attempt:\n\tYES, can be split\n\n\tPossible split:\n\t";
	while (wordIndex < wordSize) {
		if (wordIndex > wordSize) {				// for the sake of mindfullness
			cout << "Error! wordIndex beyond wordSize!" << endl;
			break;
		}
		cout << curWord.substr(wordIndex, splitVec[wordIndex]) << ' ';		// splitVec[wordIndex] is length of word in string
		wordIndex = wordIndex + splitVec[wordIndex];				// set current index to last word's ending index
	} 
	cout << "\n--------------------------------------------------------------\n";
	return; 
}
