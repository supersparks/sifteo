#ifndef OPERATOR_H
#define OPERATOR_H

#include <sifteo.h>
#include ".././GameDrawer.h"
using namespace Sifteo;

class Operator{

private:
	CubeID myCube;
	GameDrawer* myGameDrawer;

public:
	Operator(GameDrawer* gameDrawer, CubeID cubeID);
	Operator(){};
    void highlightOperator(unsigned int opSide);
    void dehighlightOperator(unsigned int opSide);
    void cleanGame();
    void repaintNewCube(unsigned int cube);
};

#endif