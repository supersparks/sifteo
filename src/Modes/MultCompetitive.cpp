#include "MultCompetitive.h"

MultCompetitive::MultCompetitive(GameDrawer* gameDrawer, int numPlayers) : PlayGame()
{
	ASSERT(Cubes::cubesConnected.size()>= 3*numPlayers);

	myGameDrawer = gameDrawer;
	myNumPlayers = numPlayers;

	for(int j=0; j < numPlayers; ++j)
	{
		totalAsked[j]=0;
		streaks[j]=0;
	}

	int i = 0;
	for(CubeID cube : CubeSet::connected())
    {
    	cubeStates[i] = CONNECTED;
    	++i;
    }

    i = 0;
    for(int i)
    while(!cubeStates[i])
    {
    	++i;
    }
    myQuestioner1 = Questioner(myGameDrawer,i);
    myQuestioners[i] = &myQuestioner1;
    cubeStates[i] = QUESTIONER;
    ++i;

    while(!cubeStates[i])
    {
    	++i;
    }
    myQuestioner2 = Questioner(myGameDrawer,i);
    myQuestioners[i] = &myQuestioner2;
    cubeStates[i] = QUESTIONER;
    ++i;

    if(myNumPlayers>=3)
    {
    	while(!cubeStates[i])
  		{
			++i;
		}
		myQuestioner3 = Questioner(myGameDrawer,i);
		myQuestioners[i] = &myQuestioner3;
		cubeStates[i] = QUESTIONER;
		++i;
	}

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
    myOperator3 = Operator(myGameDrawer,i);
    myOperators[i] = &myOperator3;
    cubeStates[i] = OPERATOR;
    ++i;
    
    while(!cubeStates[i])
    {
    	++i;
    }
    myOperator4 = Operator(myGameDrawer,i);
    myOperators[i] = &myOperator4;
    cubeStates[i] = OPERATOR;
    ++i;

    if(myNumPlayers>=3)
    {
    	    while(!cubeStates[i])
    		{
   		 	++i;
    		}
    		myOperator5 = Operator(myGameDrawer,i);
    		myOperators[i] = &myOperator5;
    		cubeStates[i] = OPERATOR;
    		++i;
    
    		while(!cubeStates[i])
    		{
    			++i;
    		}
    		myOperator6 = Operator(myGameDrawer,i);
    		myOperators[i] = &myOperator6;
    		cubeStates[i] = OPERATOR;
    		++i;
    }


    while(!cubeStates[i])
    {
    	++i;
    }
    myTimer1 = Timer(myGameDrawer,i,0);
    myTimers[i] = &myTimer1;
    cubeStates[i] = TIMER;

    while(!cubeStates[i])
    {
    	++i;
    }
    myTimer2 = Timer(myGameDrawer,i,0);
    myTimers[i] = &myTimer2;
    cubeStates[i] = TIMER;

    if(myNumPlayers>=3)
    {
    	    while(!cubeStates[i])
    		{
    			++i;
    		}
    		myTimer3 = Timer(myGameDrawer,i,0);
    		myTimers[i] = &myTimer3;
    		cubeStates[i] = TIMER;
    }

    //flush all others as not connected
    //because choosing not to constantly
    //update these values manually
    ++i;
    while(i < CUBE_ALLOCATION)
    {
    	cubeStates[i] = NOT_CONNECTED;
    	++i;
    }
}

	combinedResult = Result(0,0,0,0);
}

MultCompetitive::MultCompetitive()
{}

int MultCompetitive::runSpecificGameComms()
{
	Player1_GameOver = 0;
	Player2_GameOver = 0;
	Player3_GameOver = 0;

	//LOG("Starting runSpecificGameComms()\n");
	int i=0;
	int m=0;
	while(i < CUBE_ALLOCATION && m < numPlayers+1)
	{
		if(cubeStates[i] == QUESTIONER)
		{
			Result combinedResult[m] = myQuestioners[i]->questionUpdate();
			++m;
		}
		++i;
	}



	int j=0;
	int k=0;
	while(j < CUBE_ALLOCATION)
	{
		if(cubeStates[j] == TIMER)
		{	
			break;
		}
		++j;
	}
	if(k==0)
	{

		if( totalAsked[0] != combinedResult[0].getTotalAsked())
		{
			totalAsked[0] = combinedResult[0].getTotalAsked();
			myTimers[j]->updateResults(currResult.getCurrStreak(), currResult.getTotalCorrect());
		}

		if(myTimers[j]->gameOver())
		{
			Player1_GameOver = 1;
		}
			
		++k;
	}

	if(k==1)
	{
		if( totalAsked[1] != combinedResult[1].getTotalAsked())
		{
			totalAsked[1] = combinedResult[1].getTotalAsked();
			myTimers[j]->updateResults(combinedResult[1].getCurrStreak(), combinedResult[1].getTotalCorrect());
		}

		if(myTimers[j]->gameOver())
		{
			Player2_GameOver = 1;
		}
		if(myNumPlayers>=3)
			{++k;}
	}

	if(k==2)
	{
		if( totalAsked[2] != combinedResult[2].getTotalAsked())
		{
			totalAsked[2] = combinedResult[2].getTotalAsked();
			myTimers[j]->updateResults(combinedResult[2].getCurrStreak(), combinedResult[2].getTotalCorrect());
		}

		if(myTimers[j]->gameOver())
		{
			Player3_GameOver = 1;
		}
	}

	int l=0

	while(j < CUBE_ALLOCATION)
	{
		if(cubeStates[j] == TIMER)
		{	
			break;
		}
		++j;
	}

	if(myNumPlayers == 2 && Player1_GameOver && Player2_GameOver)
	{
		j = 0;
		while(j < CUBE_ALLOCATION)
		{
			if(cubeStates[j] == QUESTIONER)
			{	
				myQuestioners[j]->cleanGame();
			}
			++j;
		}

		k=0;
		while(k < CUBE_ALLOCATION)
		{
			if(cubeStates[k] == OPERATOR)
			{
				myOperators[k]->cleanGame();
			}
			++k;
		}
		return 1;
	}

	if(myNumPlayers == 3 && Player1_GameOver && Player2_GameOver && Player3_GameOver)
	{
		j = 0;
		while(j < CUBE_ALLOCATION)
		{
			if(cubeStates[j] == QUESTIONER)
			{	
				myQuestioners[j]->cleanGame();
			}
			++j;
		}

		k=0;
		while(k < CUBE_ALLOCATION)
		{
			if(cubeStates[k] == OPERATOR)
			{
				myOperators[k]->cleanGame();
			}
			++k;
		}
		return 1;
	}

	//LOG("About to return from runSpecificGameComms() with game not ended\n");
	return 0;

}
 No newline at end of file
