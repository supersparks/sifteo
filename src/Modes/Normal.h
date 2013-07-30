#ifndef NORMAL_H
#define NORMAL_H

#include <sifteo.h>
#include "PlayGame.h"
#include ".././GameDrawer.h"
using namespace Sifteo;

//In this mode, there an initial time constraint of 1 minute (tbc)
//with every streak  of 4 (tbc) correct answers, more time is added to the timer
class Normal : public PlayGame
{
    //TODO: set max cubes to 4 in the constructor

private:
    CubeID* myCubes;
    int totalAsked;

public:
	Normal(GameDrawer* gameDrawer);

	int getMinCubesReq();

private:
	int runSpecificGameComms();

};

#endif