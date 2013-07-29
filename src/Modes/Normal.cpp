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

    CubeID temp[1];
    questionerCubes = temp;
    CubeID temp1[2];
    operatorCubes = temp1;
    CubeID temp2[1];
    timerCubes = temp2;

    
    myQuestioners = Questioner[1];
    myOperators = Operator[2];
    myTimers = Timer[1];

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

int Normal::getMinCubesReq()
{
	return 4;
}

int Normal::runSpecificGameComms()
{
	Result currResult = myQuestioners[0].questionUpdate();
	if(currResult.getExtraTime())
	{
		myTimers[0].streakIncrease();
	}

	myTimers[0].updateResults(currResult.getCurrStreak(), currResult.getTotalCorrect());

	if(myTimers[0].gameOver())
	{
		myQuestioners[0].cleanGame();
		myOperators[0].cleanGame();
		myOperators[1].cleanGame();
		return 1;
	}
	return 0;

}