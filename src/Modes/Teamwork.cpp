#include "Teamwork.h"

Teamwork::Teamwork(GameDrawer* gameDrawer, int numPlayers) : PlayGame()
{
	LOG("Constructing Teamwork\n");
	int cubesRequired = numPlayers*3+1;
	System::setCubeRange(cubesRequired);
	myGameDrawer = gameDrawer;
	myNumPlayers = numPlayers;
	for(int i=0; i < myNumPlayers; ++i)
	{
		unbrokenStreak[i] = 0;
		playerTotalCorrect[i] = 0;
		playerTotalAsked[i] = 0;
		//LOG("Player %d, unbrokenStreak = %d, playerTotalCorrect = %d\n",
		//	i, unbrokenStreak[i], playerTotalCorrect[i]);
	}

	int i = 0;
	for(CubeID cube : CubeSet::connected())
    {
    	cubeStates[i] = CONNECTED;
    	++i;
    }

    i = 0;
    int countPlayers = 0;
    while(countPlayers < myNumPlayers)
    {
    	while(!cubeStates[i])
	    {
	    	++i;
	    }
	    myQuestionerArray[countPlayers] = Questioner(myGameDrawer,i);
	    myQuestioners[i] = &(myQuestionerArray[countPlayers]);
	    cubeStates[i] = QUESTIONER;
	    ++i;
	    while(!cubeStates[i])
	    {
	    	++i;
	    }
	    myOperatorArray[2 * countPlayers] = Operator(myGameDrawer,i);
	    myOperators[i] = &(myOperatorArray[2 * countPlayers]);
	    cubeStates[i] = OPERATOR;
	    ++i;
	    while(!cubeStates[i])
	    {
	    	++i;
	    }
	    myOperatorArray[2 * countPlayers + 1] = Operator(myGameDrawer,i);
	    myOperators[i] = &(myOperatorArray[2 * countPlayers + 1]);
	    cubeStates[i] = OPERATOR;
	    ++i;

	    if(countPlayers == 0)
	    {
	    	while(!cubeStates[i])
		    {
		    	++i;
		    }
		    myOneTimer = Timer(myGameDrawer,i,0);
		    myTimers[i] = &myOneTimer;
		    cubeStates[i] = TIMER;
		    ++i;
	    }

 	   	countPlayers++;
    }

    while(i < CUBE_ALLOCATION)
    {
    	cubeStates[i] = NOT_CONNECTED;
    	++i;
    }

	//note that the number of questioner cubes is equal to the number of players
	totalAsked = 0;
	combinedStreak = 0;

}

Teamwork::Teamwork()
{}

//returns 1 when the game has ended
//returns 0 if the game needs to keep looping
//assumes that this method is called at a raster rate than 
//the rate of the players combined can answer questions
int Teamwork::runSpecificGameComms()
{

	Result currResult[3];
	
	int questionID[3];
	int operatorID[6];
	int timerID;

	int i=0;
	int jQuestion=0;
	int jOperator=0;
	while(i < CUBE_ALLOCATION)
	{
		switch (cubeStates[i])
		{
			case (QUESTIONER) :
			{
				questionID[jQuestion] = i;
				++jQuestion;
				break;
			}
			case (OPERATOR) :
			{
				operatorID[jOperator] = i;
				++jOperator;
				break;
			}
			case (TIMER) :
			{
				timerID = i;
				break;
			}
			default:
				break;
		}
		++i;
	}

	for (int i=0; i < myNumPlayers; i++)
	{
		currResult[i] = myQuestioners[questionID[i]]->questionUpdate();
	}

	for(int i=0; i < myNumPlayers; i++)
	{
		int streak = currResult[i].getCurrStreak();
		//LOG("streak = %d\n",streak);
		if(!streak && currResult[i].getTotalAsked() > playerTotalAsked[i])
		{
			for(int j=0; j < myNumPlayers; ++j)
			{
				unbrokenStreak[j] = 0;
				playerTotalCorrect[j] = currResult[j].getTotalCorrect();
			}
			break;
		}
		unbrokenStreak[i] += (currResult[i].getTotalCorrect() - playerTotalCorrect[i]);
		playerTotalCorrect[i] = currResult[i].getTotalCorrect();
		// LOG("Player %d, unbrokenStreak = %d, playerTotalCorrect = %d, getTotalCorrect = %d\n",
		// 	i, unbrokenStreak[i], playerTotalCorrect[i], currResult[i].getTotalCorrect());
	}

	int oldCombinedStreak = combinedStreak;
	combinedStreak = 0;
	for(int i=0; i < myNumPlayers; i++)
	{
		combinedStreak += unbrokenStreak[i];
	}

	//if we need extra time then increase the time as needed on the timer
	if (!(combinedStreak % 5) && combinedStreak && oldCombinedStreak != combinedStreak)
	{
		myTimers[timerID]->streakIncrease();
	}

	int newTotalAsked = 0;
	int teamTotalCorrect = 0;
	//update totalAsked,currStreak and totalCorrect on the timer
	for(int i=0; i < myNumPlayers; i++)
	{
		newTotalAsked += currResult[i].getTotalAsked();
		playerTotalAsked[i] = currResult[i].getTotalAsked();
		teamTotalCorrect += playerTotalCorrect[i];
	}

	if( newTotalAsked > totalAsked)
	{
		totalAsked = newTotalAsked;
		myTimers[timerID]->updateResults(combinedStreak, teamTotalCorrect);
	}

	//if it is game over then clean game from all the cubes
	if(myTimers[timerID]->gameOver())
	{
		//clean game on all the questioners
		for(int i=0;i<myNumPlayers;i++)
		{
			myQuestioners[questionID[i]]->cleanGameTeamwork(teamTotalCorrect);
		}
		//LOG("Finished cleaning questioners\n");
		//cleangame on all the operators
		for(int i=0;i < 2 * myNumPlayers; i++)
		{
			myOperators[operatorID[i]]->cleanGame();
		}
		
		return 1;
	}

	return 0;
}

