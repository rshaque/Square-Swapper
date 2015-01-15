#include "unstablesquare.h"
#include "window.h"
#include "square.h"
#include <string>
#include <sstream>
#include "board.h"
#include "match.h"
#include <iostream>
using namespace std;

UnstableSquare::UnstableSquare(int colour, int row, int column) {
	this->colour = colour;
	this->row = row;
	this->column = column;
	squareSymbol = 'b';
	advancedSymbol = '_';
}

std::string UnstableSquare::getRepresentation(){
	stringstream ss;
	ss << advancedSymbol << squareSymbol << colour;
	return ss.str();
}

int UnstableSquare::executeAbility(Board* board){
	#ifdef DEBUG_UNSTABLE
	cout << "executing ability of unstable square" << endl;
	#endif
	int squaresDeleted = 0;
	int matchLength = 0;
	if (board->match){
		matchLength = board->match->length;
	}
	if (matchLength == 3){
		#ifdef DEBUG_UNSTABLE
		cout << "deleting three square match" << endl;
		#endif
		for (int c = column-1; c <= (column+1); c++){
			squaresDeleted += board->deleteSquare(row-1, c);
			squaresDeleted += board->deleteSquare(row+1, c);
		}
		squaresDeleted += board->deleteSquare(row, column-1);
		squaresDeleted += board->deleteSquare(row, column+1);
	}
	if (matchLength == 4){
		#ifdef DEBUG_UNSTABLE
		cout << "deleting four square match" << endl;
		#endif
		for (int c = (column-2); c<= (column+2); c++){
			squaresDeleted += board->deleteSquare(row-2, c);
			squaresDeleted += board->deleteSquare(row-1, c);
			squaresDeleted += board->deleteSquare(row+1, c);
			squaresDeleted += board->deleteSquare(row+2, c);
		}
		squaresDeleted += board->deleteSquare(row, column-1);
		squaresDeleted += board->deleteSquare(row, column+1);
		squaresDeleted += board->deleteSquare(row, column-2);
		squaresDeleted += board->deleteSquare(row, column+2);
	}
	return squaresDeleted;
}

void UnstableSquare::printToWindowSpecial(Xwindow* window){
	int dimension = 50;
	int x = column * dimension;
	int y = row * dimension;
	int offset = 10;
	int size = dimension - (2 * offset);
	window->fillRectangle(x + offset, y + offset, size, size, Square::blackColour);
}