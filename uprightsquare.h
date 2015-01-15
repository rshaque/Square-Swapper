#ifndef __UPRIGHT_SQUARE_H__
#define __UPRIGHT_SQUARE_H__

#include "square.h"
#include <string>

class Board;
class Xwindow;

class UprightSquare : public Square {
	public:
	UprightSquare(int colour, int row, int column);
	std::string getRepresentation();
	int executeAbility(Board* board);
	void printToWindowSpecial(Xwindow* window);
};

#endif