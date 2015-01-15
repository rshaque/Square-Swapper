#ifndef __LEVEL1_H__
#define __LEVEL1_H__

#include "level.h"
class Square;

class Level1 : public Level {
public:
	Level1();
	Square *createSquare();
	Square *createSquare(int row, int column);
	Square*** createGrid();
};

#endif