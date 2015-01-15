#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <vector>
#include <string>

class Square;

class Level {
public:
	int lockedSquares;
	int winScore;
	std::vector<int> colourList;
	unsigned int currentVPos;
	std::string file;
	Level();
	virtual Square* createSquare() = 0;
	virtual Square *createSquare(int row, int column) = 0;
	virtual Square*** createGrid() = 0;
	virtual ~Level();
	int getLockedSquares();
	void setLockedSquares(int n);
	int getWinScore();
	void setFileName(std::string fileName);
	Square*** readFromFile();
};


#endif