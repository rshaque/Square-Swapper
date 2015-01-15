#ifndef __MATCH_L_H__
#define __MATCH_L_H__

#include "match.h"

class Board;

class MatchL : public Match{
private:
	static int getNumberOfLeftMatches(int row, int col, Board* board);
	static int getNumberOfRightMatches(int row, int col, Board* board);
	static int getNumberOfAboveMatches(int row, int col, Board* board);
	static int getNumberOfBelowMatches(int row, int col, Board* board);

public:
	int endRow, endCol;
	MatchL(int row, int col, Board* board);
	static bool isMatch(int row, int col, Board* board);
	int clearCells(Board* board);
	bool insertSpecialSquare(Board* board, int squareColour);
	int getMatchColour(Board* board);
};

#endif

