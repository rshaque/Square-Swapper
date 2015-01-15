#ifndef __MATCH_VERTICAL_H__
#define __MATCH_VERTICAL_H__

#include "match.h"
class Board;

class MatchVertical : public Match {

public:
	MatchVertical(int row, int col, Board* board);
	static bool isMatch(int row, int col, Board* board);
	int clearCells(Board* board);
	bool insertSpecialSquare(Board* board, int squareColour);
	int getMatchColour(Board* board);
};

#endif