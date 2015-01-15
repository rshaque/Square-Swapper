#include <stdlib.h>
#include "level2.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include <iostream>

using namespace std;


Level2::Level2() {
	winScore = 500;
} // no locked square initially

Square* Level2::createSquare() {
	// choose a random colour
	if (colourList.size() == 0) {
		int colour;
		int x = rand() % 7 + 1;     // x in the range 1 to 6
		if (x == 1) {
			colour = 0;
		}
		else if (x == 2) {
			colour = 1;
		}
		else if (x == 3) {
			colour = 2;
		}
		else if (x == 4) {
			colour = 3;
		}
		else if (x == 5) {
			colour = 4;
		}
		else if (x == 6) {
			colour = 5;
		}
		else {
			colour = 6;
		} // end of if

		Square* newsq = new BasicSquare(colour, 0, 0);
		x = rand() % 5 + 1; // x in the range of 1 to 5
		if (x == 1) {
			newsq->setAdvSymbol("l");
			lockedSquares++;
		}
		return newsq;
	}
	else {
		int colour;
		if (currentVPos >= colourList.size()) {
			currentVPos = 0; // go back to the start of the list if you reach the end
		}
		colour = colourList[currentVPos] - '0';
		currentVPos++;
		return new BasicSquare(colour, 0, 0);
	}
} // end of createSquare()

Square* Level2::createSquare(int row, int column) {
	Square* sq = createSquare();
	sq->setCoords(row, column);
	return sq;
} // end of createSquare(int row, int column)

Square*** Level2::createGrid() {
	// create new board of 10x10 Squares
	if (file != "no file") {
		return readFromFile();
	}
	else {
		Square*** grid;
		grid = new Square**[10];
		for (int i = 0; i < 10; i++) {
			grid[i] = new Square*[10];
		}

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				grid[i][j] = createSquare();
				grid[i][j]->setCoords(i, j);
			} // end of for
		} // end of for
		return grid;
	}
} // end of createGrid()