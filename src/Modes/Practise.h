#ifndef PRACTISE_H
#define PRACTISE_H

#include <sifteo.h>
#include "PlayGame.h"
#include ".././GameDrawer.h"
using namespace Sifteo;

//In this mode, there is no time constraint
class Practise : public PlayGame
{
    //TODO: set max cubes to 4 in the constructor

private:
    CubeID* myCubes;
    int totalAsked;
    int gameEnd;
    int firstTouch;
    Questioner myQuestioner;
    Timer myTimer;
    Operator myOperator1;
    Operator myOperator2;

public:
	Practise(GameDrawer* gameDrawer);

	Practise();

	int getMinCubesReq();

	void onTouch(void *x, unsigned int id);

private:
	int runSpecificGameComms();

};

#endif