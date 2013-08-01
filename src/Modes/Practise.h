#ifndef PRACTISE_H
#define PRACTISE_H

#include <sifteo.h>
#include "PlayGame.h"
#include ".././GameDrawer.h"
using namespace Sifteo;

//In this mode, there an initial time constraint of 1 minute (tbc)
//with every streak  of 4 (tbc) correct answers, more time is added to the timer
class Practise : public PlayGame
{
    //TODO: set max cubes to 4 in the constructor

private:
    CubeID* myCubes;
    int totalAsked;
    int gameEnd;
    int firstTouch;

public:
	Practise(GameDrawer* gameDrawer);

	Practise();

	int getMinCubesReq();

	void onTouch(void *x, unsigned int id);

private:
	int runSpecificGameComms();

};

#endif