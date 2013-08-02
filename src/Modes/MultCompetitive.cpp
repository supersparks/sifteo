#include "MultCompetitive.h"

MultCompetitive::MultCompetitive(GameDrawer* gameDrawer, int numPlayers) : PlayGame()
{
	myGameDrawer = gameDrawer;
	myNumPlayers = numPlayers;
	showWhichPlayer = 1;
	showPlayerCountdown = 0;

	for(int j=0; j < numPlayers; ++j)
	{
		totalAsked[j]=0;
		streaks[j]=0;
		Player_GameOver[j] = 0;
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

    	while(!cubeStates[i])
	    {
	    	++i;
	    }
	    myTimerArray[countPlayers] = Timer(myGameDrawer,i,0);
	    myTimers[i] = &(myTimerArray[countPlayers]);
	    cubeStates[i] = TIMER;
	    ++i;

 	   	countPlayers++;
    }

    while(i < CUBE_ALLOCATION)
    {
    	cubeStates[i] = NOT_CONNECTED;
    	++i;
    }
}

MultCompetitive::MultCompetitive()
{}

int MultCompetitive::updateTime(TimeDelta delta)
{
	if(showWhichPlayer)
	{
		int questionID[3];
		int operatorID[6];
		int timerID[3];

		int i=0;
		int jQuestion=0;
		int jOperator=0;
		int jTimer = 0;
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
					timerID[jTimer] = i;
					++jTimer;
					break;
				}
				default:
					break;
			}
			++i;
		}

		showPlayerCountdown += delta.seconds();
		if((int) showPlayerCountdown >= 3)
		{
			showWhichPlayer = 0;
			for(int i=0; i < myNumPlayers; ++i)
			{
				myTimers[timerID[i]]->repaintNewCube(timerID[i]);
			}
		}
		else
		{
			for(int i=0; i < myNumPlayers; ++i)
			{
				myGameDrawer->drawWhichPlayer(timerID[i], i);
				myGameDrawer->drawWhichPlayer(questionID[i], i);
			}
		}
	}
	else
	{
		return PlayGame::updateTime(delta);
	}

	return 0;
}

int MultCompetitive::runSpecificGameComms()
{
	//LOG("Starting runSpecificGameComms()\n");
	int questionID[3];
	int operatorID[6];
	int timerID[3];

	int i=0;
	int jQuestion=0;
	int jOperator=0;
	int jTimer = 0;
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
				timerID[jTimer] = i;
				++jTimer;
				break;
			}
			default:
				break;
		}
		++i;
	}

	for (int j=0; j < myNumPlayers; j++)
	{
		currResult[j] = myQuestioners[questionID[j]]->questionUpdate();
	}

	for(int j=0; j< myNumPlayers; ++j)
	{
		if(currResult[j].getExtraTime())
		{
			myTimers[timerID[j]]->streakIncrease();
		}

		if( totalAsked[j] != currResult[j].getTotalAsked())
		{
			//LOG("Player %d has answered %d questions\n", j, currResult[j].getTotalAsked());
			totalAsked[j] = currResult[j].getTotalAsked();
			myTimers[timerID[j]]->updateResults(currResult[j].getCurrStreak(), currResult[j].getTotalCorrect());
		}

		if(myTimers[timerID[j]]->gameOver())
		{
			Player_GameOver[j] = 1;

			myQuestioners[questionID[j]]->cleanGame();
		}
	}

	int endGameNow = 1;
	for(int j=0; j < myNumPlayers; ++j)
	{
		endGameNow *= Player_GameOver[j];
	}

	//LOG("About to do endGameNow if statement\n");
	if(endGameNow)
	{
		LOG("Ending game now\n");
		for(int j=0; j < 2 * myNumPlayers; ++j)
		{
			myOperators[operatorID[j]]->cleanGame();
		}
		LOG("Cleaned operators\n");
		int winner = 0;
		for(int j = 1; j < myNumPlayers; ++j)
		{
			if( currResult[winner].getTotalCorrect() < currResult[j].getTotalCorrect())
			{
				winner = j;
			}
		}
		LOG("About to print final game over screen");
		for(int j=0; j < myNumPlayers; ++j)
		{
			myQuestioners[questionID[j]]->cleanGameMultiplayer(winner, currResult[winner].getTotalCorrect());
		}
		LOG("About to return from runSpecificGameComms() with game ended\n");
	}
	return endGameNow;

}
