#ifndef __PSYCHEDELIC_SQUARE_H__
#define __PSYCHEDELIC_SQUARE_H__

#include "square.h"
#include <string>

class Board;
class Xwindow;

class PsychedelicSquare : public Square {
	public:
	PsychedelicSquare(int colour, int row, int column);
	std::string getRepresentation();
	int executeAbility(Board* board);
	void printToWindowSpecial(Xwindow* window);
};

#endif