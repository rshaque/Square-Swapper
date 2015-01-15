#ifndef __MATCH_HORIZONTAL_H__
#define __MATCH_HORIZONTAL_H__

#include "match.h"
class Board;

class MatchHorizontal : public Match{

public:
	MatchHorizontal(int row, int col, Board* board);
	static bool isMatch(int row, int col, Board* board);
	int clearCells(Board* board);
	bool insertSpecialSquare(Board* board, int squareColour);
	int getMatchColour(Board* board);
};

#endif