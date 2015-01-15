#ifndef __MATCH_H__
#define __MATCH_H__

#include "square.h"
class Board;

class Match{

protected:
	int cellsDeleted;

public:
	static int maxRow;
	static int maxCol;
	int length;

public:
	int row, col;
	virtual int clearCells(Board* board) = 0;
	virtual bool insertSpecialSquare(Board* board, int squareColour) = 0;
	virtual int getMatchColour(Board* board) = 0;
};
#endif