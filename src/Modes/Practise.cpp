#include "Practise.h"

Practise::Practise(GameDrawer* gameDrawer) : PlayGame()
{
	System::setCubeRange(4);
	myGameDrawer = gameDrawer;
	totalAsked = 0;
	gameEnd = 0;
	firstTouch = 1;

	int i = 0;
	for(CubeID cube : CubeSet::connected())
    {
    	cubeStates[i] = CONNECTED;
    	++i;
    }

    i = 0;
    while(!cubeStates[i])
    {
    	++i;
    }
    myQuestioner = Questioner(myGameDrawer,i);
    myQuestioners[i] = &myQuestioner;
    cubeStates[i] = QUESTIONER;
    ++i;
    while(!cubeStates[i])
    {
    	++i;
    }
    myOperator1 = Operator(myGameDrawer,i);
    myOperators[i] = &myOperator1;
    cubeStates[i] = OPERATOR;
    ++i;
    while(!cubeStates[i])
    {
    	++i;
    }
    myOperator2 = Operator(myGameDrawer,i);
    myOperators[i] = &myOperator2;
    cubeStates[i] = OPERATOR;
    ++i;
    while(!cubeStates[i])
    {
    	++i;
    }
    myTimer = Timer(myGameDrawer,i,1);
    myTimers[i] = &myTimer;
    cubeStates[i] = TIMER;

    ++i;
    while(i < CUBE_ALLOCATION)
    {
    	cubeStates[i] = NOT_CONNECTED;
    	++i;
    }

}

Practise::Practise()
{}

void Practise::onTouch(void *x, unsigned int id)
{
	//LOG("Practise touched onEndScreen = %d, id = %d \n",onEndScreen,id);
	if(!ending)
	{
		if(cubeStates[id] == QUESTIONER)
		{
			myQuestioners[id]->cleanGame();

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
			myOperators[k]->cleanGame();
			myOperators[l]->cleanGame();

			int m=0;
			while(m < CUBE_ALLOCATION)
			{
				if(cubeStates[m] == TIMER)
				{
					break;
				}
				++m;
			}
			myGameDrawer->switchToBG0(m);
			myGameDrawer->paintBlack(m);
			ending = 1;
			gameEnd = 1;
		}
		//endingFromPractise();
	}
	else if(!firstTouch)
	{
		if(cubeStates[id] == QUESTIONER)
		{
			myGameDrawer->paintBlack(id);
			myGameDrawer->doPanning(id,vec(0,0));
			ended = 1;
		}
	}
	else
	{	
		if(cubeStates[id] == QUESTIONER)
		{
			firstTouch = 0;
		}
	}
}

int Practise::runSpecificGameComms()
{

	int i=0;
	while(i < CUBE_ALLOCATION)
	{
		if(cubeStates[i] == QUESTIONER)
		{
			break;
		}
		++i;
	}
	Result currResult = myQuestioners[i]->questionUpdate();


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
		myTimers[j]->updateResults(currResult.getCurrStreak(), currResult.getTotalCorrect());
	}

	//LOG("About to return from runSpecificGameComms() with game not ended\n");


	return gameEnd;

}