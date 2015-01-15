#ifndef __UNSTABLE_SQUARE_H__
#define __UNSTABLE_SQUARE_H__

#include "square.h"
#include <string>

class Board;
class Xwindow;

class UnstableSquare : public Square {
	public:
	UnstableSquare(int colour, int row, int column);
	std::string getRepresentation();
	int executeAbility(Board* board);
	void printToWindowSpecial(Xwindow* window);
};

#endif