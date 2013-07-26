#include "Normal.h"

Normal::Normal(GameDrawer* gameDrawer)
{
	PlayGame();
	int i = 0;
	for(CubeID cube : CubeSet::connected())
    {
    	myCubes[i] = cube;
    	++i;
    }

    questionerCubes = new int[1];
    operatorCubes = new int[2];
    timerCubes = new int[1];
    myQuestioners = new int[1];
    myOperators = new int[2];
    myTimers = new int[1];

	myDrawer = gameDrawer;

	myQuestioners[0] = Questioner(myDrawer,myCubes[0]);
	questionerCubes[0] = myCubes[0];

	myOperators[0] = Operator(myDrawer,myCubes[1]);
	operatorCubes[0] = myCubes[1];
	myOperators[1] = Operator(myDrawer,myCubes[2]);
	operatorCubes[1] = myCubes[2];

	myTimers[0] = Timer(myDrawer,myCubes[3]);
	timerCubes[0] = myCubes[3];
}

Normal::getMinCubesReq()
{
	return 4;
}

Normal::runSpecificGameComms()
{
	
}