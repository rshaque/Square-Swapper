#ifndef __BASIC_SQUARE_H__
#define __BASIC_SQUARE_H__

#include "square.h"
#include <string>

class Board;
class Xwindow;

class BasicSquare : public Square {
public:
	BasicSquare(int colour, int row, int column);
	std::string getRepresentation();
	int executeAbility(Board* board);
	void printToWindowSpecial(Xwindow* window);
};

#endif