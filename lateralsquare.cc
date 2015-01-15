#include "lateralsquare.h"
#include "board.h"
#include "square.h"
#include "window.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

LateralSquare::LateralSquare(int colour, int row, int column) {
	this->colour = colour;
	this->row = row;
	this->column = column;
	squareSymbol = 'h';
	advancedSymbol = '_';
}

std::string LateralSquare::getRepresentation(){
	stringstream ss;
	ss << advancedSymbol << squareSymbol << colour;
	return ss.str();
}

int LateralSquare::executeAbility(Board* board){
	int squaresDeleted = 0;
	for (int c = 0; c < column; c++){
		#ifdef DEBUG

		cout << "deleting from LateralSquare ability, row: " << row << ", col: " << c << endl;
		#endif
		squaresDeleted += board->deleteSquare(row, c);
	}
	for (int c = (column + 1); c < 10; c++){
		squaresDeleted += board->deleteSquare(row, c);
	}
	return squaresDeleted;
}

void LateralSquare::printToWindowSpecial(Xwindow* window){
	int dimension = 50;
	int x = column * dimension;
	int y = row * dimension;
	int stripeHeight = 10;
	// window->fillRectangle(this->column*dimension, this->row*dimension, dimension, dimension, colour);
	window->fillRectangle(x, y, dimension, stripeHeight, colour);
	window->fillRectangle(x, (y + stripeHeight), dimension, stripeHeight, Square::blackColour);

	window->fillRectangle(x, (y + (stripeHeight*2)), dimension, stripeHeight, colour);
	window->fillRectangle(x, (y + (stripeHeight*3)), dimension, stripeHeight, Square::blackColour);

	window->fillRectangle(x, (y + (stripeHeight*4)), dimension, stripeHeight, colour);
}

/*
int LateralSquare::executeAbility(Square*** grid, int gridsMatched){
	int squaresDeleted = 0;
	for (int i = 0; i < column; i++){
		squaresDeleted += 1;
		delete grid[row][i];
		grid[row][i] = NULL;
	}
	for (int i = (column + 1); i < 10; i++){
		squaresDeleted += 1;
		delete grid[row][i];
		grid[row][i] = NULL;
	}
	return squaresDeleted;
}
*/