#include "Questioner.h"


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

    //LOG("Created first question for Questioner %d\n", (int) cubeId);
}

void Questioner::countdownOver()
{
	//LOG("Questioner cube is %d\n",(int) myCube );
	myGameDrawer->drawQuestionerBackground(myCube);
	currQuestion = Question(myGameDrawer, myCube, yCurrQuestion);
}

void Questioner::repaintNewCube(unsigned int cube)
{
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

Result Questioner::questionUpdate()
{
	if(extraTime)
	{
		extraTime = 0;
		return Result(currStreak, totalCorrect, 1, totalAsked);
	}
	else
	{
		return Result(currStreak, totalCorrect, 0, totalAsked);
	}
}

void Questioner::cleanGame()
{
	//Do something with memory adding longestStreak, totalAsked, totalCorrect
	myGameDrawer->paintGameOver(myCube, totalCorrect, longestStreak);
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
	float panningPropTimeLeft = (TIME_TO_SCROLL - timetaken) / (float) TIME_TO_SCROLL;
	
	Float2 diffPan = vec((float) 0, panningPropTimeLeft * PIXEL_SCROLL);
	Float2 newPan = targetPan + diffPan;

	myGameDrawer->doPanning(myCube, newPan.round());

	return newPan.round();
}