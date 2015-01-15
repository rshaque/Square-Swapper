#include "level.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

Level::Level() {
	colourList = vector<int>(0,0);
	currentVPos = 0;
	file = "no file"; 
	lockedSquares = 0;
	winScore = 0;
}

int Level::getLockedSquares() {
	return lockedSquares;
}

void Level::setLockedSquares(int n) {
	lockedSquares = n;
}

void Level::setFileName(string fileName) {
	file = fileName;
}

Square*** Level::readFromFile() {
	// create new board of 10x10 Squares
	Square*** grid;
	grid = new Square**[10];
	for (int i = 0; i < 10; i++) {
		grid[i] = new Square*[10];
	}
	int colour;
	char type;

	ifstream in(file.c_str());
	string input;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			in >> input;
			const char* csqr = input.c_str();
			type = csqr[1];
			colour = csqr[2] - '0';
			if (type == '_') {
				grid[i][j] = new BasicSquare(colour, i, j);
			}
			else if (type == 'h') {
				grid[i][j] = new LateralSquare(colour, i, j);
			}
			else if (type == 'v') {
				grid[i][j] = new UprightSquare(colour, i, j);
			}
			else if (type == 'b') {
				grid[i][j] = new UnstableSquare(colour, i, j);
			}
			else {
				grid[i][j] = new PsychedelicSquare(colour, i, j);
			} // end of if
		} // end of for
	} // end of for

	
	if (in >> input) {
		const char* clist = input.c_str();
		for (unsigned int i = 0; i < input.length(); i++) {
			colourList.push_back((int)clist[i]);
		} // end of for
	} // colourlist

	return grid;
}

int Level::getWinScore() {
	return winScore;
}

Level::~Level(){

}