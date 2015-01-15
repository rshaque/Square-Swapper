#ifndef __LEVEL2_H__
#define __LEVEL2_H__

#include "level.h"
#include "square.h"

class Level2 : public Level {
public:
	Level2();
	Square *createSquare();
	Square *createSquare(int row, int column);
	Square*** createGrid();
};


#endif