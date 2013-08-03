#include "Questioner.h"

StoredObject Questioner::s_HighScore = StoredObject(255);
StoredObject Questioner::s_LongestStreak = StoredObject(254);
StoredObject Questioner::s_TotalAsked = StoredObject(253);

Questioner::Questioner(GameDrawer* gameDrawer, CubeID cubeId)
{
	myCube = cubeId;
	myGameDrawer = gameDrawer;

	currStreak = 0;
	totalAsked = 0;
	totalCorrect = 0;
	longestStreak = 0;

	yCurrQuestion = FIRST_QUESTION_HEIGHT;

	currPan = vec(0,0);
    targetPan = vec(0,0);

    timePanning = 0;
    panning = 0;
    corrQuestAns = 0;
    extraTime = 0;
    gameEnded = 0;

    //LOG("Created first question for Questioner %d\n", (int) cubeId);
}

void Questioner::countdownOver()
{
	//LOG("Questioner cube is %d\n",(int) myCube );
	myGameDrawer->drawQuestionerBackground(myCube);
	currQuestion = Question(myGameDrawer, myCube, yCurrQuestion);
	prevQuestion = Question(myCube);
}

void Questioner::repaintNewCube(unsigned int cube)
{
	//LOG("repainting New Questioner Cube\n");
	myCube = cube;
	myGameDrawer->drawQuestionerBackground(myCube);

	currPan = vec(0,0);
	targetPan = vec(0,0);
	yCurrQuestion = FIRST_QUESTION_HEIGHT;

	int *questionHolder;

	if(panning)
	{
		panning = 0;

		if( currPan == targetPan)
		{
			if(currQuestion.equals(prevQuestion))
			{
				currQuestion = newQuestion;
				//print both curr and prev
				questionHolder = currQuestion.retrieveQuestion();
				currQuestion = Question(myGameDrawer, myCube, 4, questionHolder,0);
				questionHolder = prevQuestion.retrieveQuestion();
				prevQuestion = Question(myGameDrawer, myCube, 8, questionHolder,1);
			}
			else
			{
				currQuestion = newQuestion;
				//print just curr
				questionHolder = currQuestion.retrieveQuestion();
				currQuestion = Question(myGameDrawer, myCube, 4, questionHolder,0);
			}
		}
		else
		{
			prevQuestion = currQuestion;
			currQuestion = newQuestion;
			//print both curr and prev
			questionHolder = currQuestion.retrieveQuestion();
			currQuestion = Question(myGameDrawer, myCube, 4, questionHolder,0);
			questionHolder = prevQuestion.retrieveQuestion();
			prevQuestion = Question(myGameDrawer, myCube, 8, questionHolder,1);
		}
	}
	else
	{
		//print curr and prev
		if(totalAsked)
		{
			questionHolder = currQuestion.retrieveQuestion();
			currQuestion = Question(myGameDrawer, myCube, 4, questionHolder,0);
			questionHolder = prevQuestion.retrieveQuestion();
			prevQuestion = Question(myGameDrawer, myCube, 8, questionHolder,1);
		}
		else
		{
			questionHolder = currQuestion.retrieveQuestion();
			currQuestion = Question(myGameDrawer, myCube, 4, questionHolder,0);
		}
	}
}

void Questioner::runGame(TimeDelta myDelta)
{

	if(panning)
	{
		timePanning += myDelta.milliseconds();
		if(timePanning > TIME_TO_CORRECT && !corrQuestAns)
		{
			corrQuestAns = 1;
			currQuestion.updateToCorrect();
		}

		currPan = doPanning(targetPan,timePanning);
		if(currPan == targetPan)
		{
			prevQuestion.clean();
			prevQuestion = currQuestion;
			currQuestion = newQuestion;
			panning = 0;
		}
	}
	else if(currQuestion.answered())
	{
		yCurrQuestion = yCurrQuestion - 6;
		if(yCurrQuestion < 0)
		{
			yCurrQuestion += 18;
		}
		newQuestion = Question(myGameDrawer, myCube, yCurrQuestion);

		targetPan = currPan - vec(0,48);
		if(currPan.y < 0)
		{
			targetPan.y = targetPan.y += 144;
			currPan.y = currPan.y += 144;
		}

		timePanning = 0;
		panning = 1;
		corrQuestAns = 0;

		int correct = currQuestion.wasRight();

		if(!correct)
		{
			if(longestStreak < currStreak)
			{
				longestStreak = currStreak;
			}
			currStreak = 0;
		}                                                                                                                                        
		else
		{
			currStreak += correct;
			//LOG("currStreak = %d questioner with cubeID = %d\n",currStreak, (int)myCube);
			totalCorrect += correct;
			if(!(currStreak % 5))
			{
				extraTime = 1;
			}
		}
		totalAsked++;
	}

	//LOG("Questioner about to return runGame()\n");
}

//returns the most recent result
Result Questioner::questionUpdate()
{
	//LOG("questionUpdate being called from questioner with cubeID = %d\n",(int)myCube);
	if(extraTime)
	{
		extraTime = 0;
		return Result(currStreak, totalCorrect, 1, totalAsked);
	}
	else
	{
		//if (currStreak>=1) LOG("currStreak = %d\n",currStreak);
		return Result(currStreak, totalCorrect, 0, totalAsked);
	}
}

void Questioner::initStoredObjects()
{
	void* buff;
	//no highscore has been saved before
	if (s_HighScore.readObject(buff,0) <= 0)
	{
		//we asssume that s_highscore hasn't been written to before
		//if and only if s_longestStreeam and s_TotalAsked hasn't 
		//been written to before
		s_HighScore.writeObject(0);
		s_LongestStreak.writeObject(0);
		s_TotalAsked.writeObject(0);
	}
}

void Questioner::cleanGame()
{
	if(!gameEnded)
	{
		if(currStreak > longestStreak)
		{
			longestStreak = currStreak;
		}

		initStoredObjects();

		int prevHighscore = -1;
		s_HighScore.readObject(prevHighscore,0);
		//LOG("prevHighscore = %d\n",prevHighscore);
		if (prevHighscore<totalCorrect)	s_HighScore.write(totalCorrect);

		int prevLongestStreak = -1;
		s_LongestStreak.readObject(prevLongestStreak,0);
		//LOG("prevLongestStreak = %d\n",prevLongestStreak);
		if (prevLongestStreak<longestStreak) s_LongestStreak.write(longestStreak);

		int prevTotalAsked = -1;
		s_TotalAsked.readObject(prevTotalAsked,0);
		//LOG("prevTotalAsked = %d\n",prevTotalAsked);
		int newTotalAsked = prevTotalAsked + totalAsked;
		s_TotalAsked.write(newTotalAsked);

		myGameDrawer->paintGameOver(myCube, totalCorrect, longestStreak);

		gameEnded = 1;
	}
}

void Questioner::cleanGameTeamwork(int teamTotalCorrect)
{
	if(currStreak > longestStreak)
	{
		longestStreak = currStreak;
	}

	initStoredObjects();

	int prevHighscore = -1;
	s_HighScore.readObject(prevHighscore,0);
	//LOG("prevHighscore = %d\n",prevHighscore);
	if (prevHighscore<totalCorrect)	s_HighScore.write(totalCorrect);

	int prevLongestStreak = -1;
	s_LongestStreak.readObject(prevLongestStreak,0);
	//LOG("prevLongestStreak = %d\n",prevLongestStreak);
	if (prevLongestStreak<longestStreak) s_LongestStreak.write(longestStreak);

	int prevTotalAsked = -1;
	s_TotalAsked.readObject(prevTotalAsked,0);
	//LOG("prevTotalAsked = %d\n",prevTotalAsked);
	int newTotalAsked = prevTotalAsked + totalAsked;
	s_TotalAsked.write(newTotalAsked);

	myGameDrawer->paintGameOverTeamwork(myCube, totalCorrect, longestStreak, teamTotalCorrect);
}

void Questioner::cleanGameMultiplayer(int winner, int winnerScore)
{
	if(!gameEnded)
	{
		if(currStreak > longestStreak)
		{
			longestStreak = currStreak;
		}

		initStoredObjects();

		int prevHighscore = -1;
		s_HighScore.readObject(prevHighscore,0);
		//LOG("prevHighscore = %d\n",prevHighscore);
		if (prevHighscore<totalCorrect)	s_HighScore.write(totalCorrect);

		int prevLongestStreak = -1;
		s_LongestStreak.readObject(prevLongestStreak,0);
		//LOG("prevLongestStreak = %d\n",prevLongestStreak);
		if (prevLongestStreak<longestStreak) s_LongestStreak.write(longestStreak);

		int prevTotalAsked = -1;
		s_TotalAsked.readObject(prevTotalAsked,0);
		//LOG("prevTotalAsked = %d\n",prevTotalAsked);
		int newTotalAsked = prevTotalAsked + totalAsked;
		s_TotalAsked.write(newTotalAsked);
	}

	myGameDrawer->paintGameOverMultiplayer(myCube, totalCorrect
		, longestStreak, winner, winnerScore);
}

void Questioner::inputOperator(int mySide,int opType)
{
	int opPos = 1;
	if(mySide == RIGHT)
	{
		opPos = 2;
	}

	currQuestion.printOperator(opType, opPos);
}

void Questioner::removeOperator(unsigned int mySide)
{
	int opPos = 1;
	if(mySide == RIGHT)
	{
		opPos = 2;
	}

	currQuestion.removeOperator(opPos);
}

Int2 Questioner::doPanning(Int2 targetPan, int timetaken)
{
	if(timetaken > TIME_TO_SCROLL)
	{
		myGameDrawer->doPanning(myCube, targetPan);
		return targetPan;
	}

	float panningPropTimeLeft = (TIME_TO_SCROLL - timetaken) / (float) TIME_TO_SCROLL;
	
	Float2 diffPan = vec((float) 0, panningPropTimeLeft * PIXEL_SCROLL);
	Float2 newPan = targetPan + diffPan;

	myGameDrawer->doPanning(myCube, newPan.round());

	return newPan.round();
}