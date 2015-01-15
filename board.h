#ifndef __BOARD_H__
#define __BOARD_H__

#include "square.h"
#include "level.h"
#include "level0.h"
#include "level1.h"
#include "level2.h"
#include <string>
#include <vector>
#include <iostream>

class Match;
class Xwindow;
class Level;

class Board {
	int level;
	int movesRemaining;
	Square*** grid;
	// TextDisplay* td;
	Level* lvl;

private:
	bool textOnly;
	std::string fileName;
public:

	int score;
	int winScore;
	Xwindow* window;
	Match* match;
	Board(std::string fileName, int lvlNum, bool textOnly, std::string colourScheme);
	~Board();
	bool determineMatches();
	int executeMatches();
	void updateBoard();
	int getScore();
	void setScore(int newScore);
	int getLevel();
	void setLevel(int newLevel);
	void setGrid(Square*** grid);
	Square*** getGrid();
	void swap (int row, int column, int direction);
	void getHint();
	void putRandom(int row, int column);
	int getRemainingMoves();
	int getLockedSquares();
	int getPoints(int squares, int chain);
	void scramble();
	void levelup();
	void leveldown();
	void restart();
	void initBoard();
	void refill();
	void setGridElement(int r, int c, Square* sqr);
	int deleteSquare(int r, int c);	
	void setTextOnly(bool textOnly);
	friend std::ostream& operator<< (std::ostream &out, Board &b);
};

#endif