#include <cstdlib>
#include "level1.h"
#include "basicsquare.h"
#include "lateralsquare.h"
#include "uprightsquare.h"
#include "unstablesquare.h"
#include "psychedelicsquare.h"
#include <iostream>

using namespace std;


Level1::Level1() {
	winScore = 300; 
} // next created square is #1

Square* Level1::createSquare() {
	// choose a random colour based on probabilities
	if (colourList.size() == 0) {
		int colour;
		int x = rand() % 9 + 1;     // x in the range 1 to 9
		if (x == 1 || x == 2) {
			colour = 0;
		}
		else if (x == 3 || x == 4) {
			colour = 1;
		}
		else if (x == 5) {
			colour = 2;
		}
		else if (x == 6) {
			colour = 3;
		} // end of if
		else if (x == 7) {
			colour = 4;
		}
		else if (x == 8) {
			colour = 5;
		}
		else {
			colour = 6;
		}

		// choose a type of square to create (basic if squareNumber = 1-4, special if  = multiple of 5)
		x = rand() % 10 + 1; // x in the range of 1 to 5
		if (x == 1) {
			// choose a type of special square to create
			x = rand() % 4 + 1;		// x in the range of 1 to 4
			if (x == 1) {
				return new LateralSquare(colour, 0, 0);
			}
			else if (x == 2) {
				return new PsychedelicSquare(colour, 0, 0);
			}
			else if (x == 3) {
				return new UnstableSquare(colour, 0, 0);
			}
			else {
				return new UprightSquare(colour, 0, 0);
			} // end of if
		} // end of if
		else {
			return new BasicSquare(colour, 0, 0);
		}
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

Square* Level1::createSquare(int row, int column) {
	Square* sq = createSquare();
	sq->setCoords(row, column);
	return sq;
} // end of createSquare(int row, int column)

Square*** Level1::createGrid() {
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