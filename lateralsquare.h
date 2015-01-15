#ifndef __LATERAL_SQUARE_H__
#define __LATERAL_SQUARE_H__

#include "square.h"
#include <string>

class Board;
class Xwindow;

class LateralSquare : public Square {
public:
	LateralSquare(int colour, int row, int column);
	std::string getRepresentation();
	int executeAbility(Board* board);
	void printToWindowSpecial(Xwindow* window);
};

#endif