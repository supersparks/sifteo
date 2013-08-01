#include "Practise.h"

Practise::Practise(GameDrawer* gameDrawer) : PlayGame()
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

Practise::Practise()
{}

int Practise::getMinCubesReq()
{
	return 4;
}

void Practise::onTouch(void *x, unsigned int id)
{
	LOG("Practise touched \n");
	int i=0;
	while (i< CUBE_ALLOCATION)
	{
		if(cubeStates[i] == QUESTIONER)
		{
			break;
		}
		++i;
	}
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

	int m=0;
	while(m < CUBE_ALLOCATION)
	{
		if(cubeStates[m] == TIMER)
		{
			break;
		}
		++l;
	}
	myTimers[m].gameOver();
}

int Practise::runSpecificGameComms()
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

	if( totalAsked != currResult.getTotalAsked())
	{
		totalAsked = currResult.getTotalAsked();
		myTimers[j].updateResults(currResult.getCurrStreak(), currResult.getTotalCorrect());
	}

	//LOG("About to return from runSpecificGameComms() with game not ended\n");
	int n = 0;


	return 0;

}