#include "psychedelicsquare.h"
#include "board.h"
#include "window.h"
#include "square.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

PsychedelicSquare::PsychedelicSquare(int colour, int row, int column) {
	this->colour = colour;
	this->row = row;
	this->column = column;
	squareSymbol = 'p';
	advancedSymbol = '_';
}

std::string PsychedelicSquare::getRepresentation(){
	stringstream ss;
	ss << advancedSymbol << squareSymbol << colour;
	return ss.str();
}

int PsychedelicSquare::executeAbility(Board* board){
	int squaresDeleted = 0;

	Square*** grid = board->getGrid();
	#ifdef DEBUG
	cout << "executeAbility of PsychedelicSquare" << endl;
	#endif
	for (int r = 0; r < 10; r++){
		for (int c = 0; c < 10; c++){
			if (grid[r][c] && (r!=row || c!=column) && ((grid[r][c]->getColour()) == colour)){
				squaresDeleted += board->deleteSquare(r, c);
				#ifdef DEBUG
				cout << "delete square PsychedelicSquare" << endl;
				#endif
			}
		}
	}
	return squaresDeleted;
}

void PsychedelicSquare::printToWindowSpecial(Xwindow* window){
	int dimension = 50;
	int x = column * dimension;
	int y = row * dimension;
	int width = dimension / 3;
	int length = dimension;
	int offset = dimension / 3;
	window->fillRectangle(x+offset, y, width, length, Square::blackColour);
	window->fillRectangle(x, y+offset, length, width, Square::blackColour);
}