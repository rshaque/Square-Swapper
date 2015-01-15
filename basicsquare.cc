#include "basicsquare.h"
#include "window.h"
#include <string>
#include <sstream>
using namespace std;

class Board;

BasicSquare::BasicSquare(int colour, int row, int column) {
	this->colour = colour;
	this->row = row;
	this->column = column;
	squareSymbol = '_';
	advancedSymbol = '_';
}

std::string BasicSquare::getRepresentation(){
	stringstream ss;
	ss << advancedSymbol << squareSymbol << colour;
	return ss.str();
}

int BasicSquare::executeAbility(Board* board){
	return 0;
}

void BasicSquare::printToWindowSpecial(Xwindow* window){
	
}