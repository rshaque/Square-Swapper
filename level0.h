#ifndef __LEVEL0_H__
#define __LEVEL0_H__
#include "level.h"

class Square;

class Level0 : public Level {
public:
	Level0();
	Square *createSquare();
	Square *createSquare(int row, int column);
	Square*** createGrid();
};


#endif