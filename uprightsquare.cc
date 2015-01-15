#include "uprightsquare.h"
#include "board.h"
#include "window.h"
#include "square.h"
#include <string>
#include <sstream>
using namespace std;

UprightSquare::UprightSquare(int colour, int row, int column) {
	this->colour = colour;
	this->row = row;
	this->column = column;
	squareSymbol = 'v';
	advancedSymbol = '_';
}

std::string UprightSquare::getRepresentation(){
	stringstream ss;
	ss << advancedSymbol << squareSymbol << colour;
	return ss.str();
}

int UprightSquare::executeAbility(Board* board){
	int squaresDeleted = 0;	
	for (int r = 0; r < row; r++){
		squaresDeleted += board->deleteSquare(r, column);
	}
	for (int r = row+1; r < 10; r++){
		squaresDeleted += board->deleteSquare(r, column);
	}

	return squaresDeleted;
}

void UprightSquare::printToWindowSpecial(Xwindow* window){
	int dimension = 50;
	int x = column * dimension;
	int y = row * dimension;
	int stripeWidth = 10;
	window->fillRectangle((x + (stripeWidth * 0)), y, stripeWidth, dimension, colour);
	window->fillRectangle((x + (stripeWidth * 1)), y, stripeWidth, dimension, Square::blackColour);

	window->fillRectangle((x + (stripeWidth * 2)), y, stripeWidth, dimension, colour);
	window->fillRectangle((x + (stripeWidth * 3)), y, stripeWidth, dimension, Square::blackColour);

	window->fillRectangle((x + (stripeWidth * 4)), y, stripeWidth, dimension, colour);
}

/*
void LateralSquare::printToWindowSpecial(Xwindow* window){
	int dimension = 50;
	int x = column * dimension;
	int y = row * dimension;
	int stripeHeight = 10;
	// window->fillRectangle(this->column*dimension, this->row*dimension, dimension, dimension, colour);
	window->fillRectangle(x, y, dimension, stripeHeight, colour);
	window->fillRectangle(x, (y + stripeHeight), dimension, stripeHeight, 5);

	window->fillRectangle(x, (y + (stripeHeight*2)), dimension, stripeHeight, colour);
	window->fillRectangle(x, (y + (stripeHeight*3)), dimension, stripeHeight, 5);

	window->fillRectangle(x, (y + (stripeHeight*4)), dimension, stripeHeight, colour);
}
*/