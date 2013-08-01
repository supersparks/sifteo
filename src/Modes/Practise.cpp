#include "Normal.h"

Normal::Normal(GameDrawer* gameDrawer) : PlayGame()
{
	myGameDrawer = gameDrawer;
	totalAsked = 0;

	int i = 0;
	for(CubeID cube : CubeSet::connected())
    {
    	cubeStates[i] = QUESTIONER;
    	++i;
    }

    i = 0;
    while(!cubeStates[i])
    {
    	++i;
    }
    myQuestioners[i] = Questioner(myGameDrawer,i);
    cubeStates[i] = QUESTIONER;
    ++i;
    while(!cubeStates[i])
    {
    	++i;
    }
    myOperators[i] = Operator(myGameDrawer,i);
    cubeStates[i] = OPERATOR;
    ++i;
    while(!cubeStates[i])
    {
    	++i;
    }
    myOperators[i] = Operator(myGameDrawer,i);
    cubeStates[i] = OPERATOR;
    ++i;
    while(!cubeStates[i])
    {
    	++i;
    }
    myTimers[i] = Timer(myGameDrawer,i);
    cubeStates[i] = TIMER;

}

Normal::Normal()
{}

int Normal::getMinCubesReq()
{
	return 4;
}

int Normal::runSpecificGameComms()
{
	//LOG("Starting runSpecificGameComms()\n");
	int i=0;
	while(i < CUBE_ALLOCATION)
	{
		if(cubeStates[i] == QUESTIONER)
		{
			break;
		}
		++i;
	}
	Result currResult = myQuestioners[i].questionUpdate();


	int j=0;
	while(j < CUBE_ALLOCATION)
	{
		if(cubeStates[j] == TIMER)
		{
			break;
		}
		++j;
	}
	// if(currResult.getExtraTime())
	// {
	// 	myTimers[j].streakIncrease();
	// }

	if( totalAsked != currResult.getTotalAsked())
	{
		totalAsked = currResult.getTotalAsked();
		myTimers[j].updateResults(currResult.getCurrStreak(), currResult.getTotalCorrect());
	}

	if(myTimers[j].gameOver())
	{
		myQuestioners[i].cleanGame();
		int k=0;
		while(k < CUBE_ALLOCATION)
		{
			if(cubeStates[k] == OPERATOR)
			{
				break;
			}
			++k;
		}
		int l=k+1;
		while(l < CUBE_ALLOCATION)
		{
			if(cubeStates[l] == OPERATOR)
			{
				break;
			}
			++l;
		}
		myOperators[k].cleanGame();
		myOperators[l].cleanGame();
		return 1;
	}

	//LOG("About to return from runSpecificGameComms() with game not ended\n");
	return 0;

}