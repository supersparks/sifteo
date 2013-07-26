#include "Questioner.h"


Questioner::Questioner(GameDrawer gameDrawer, CubeID cubeId){
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

    currQuestion = Question(myCube, yCurrQuestion);
}

void Questioner::runGame(TimeDelta myDelta)
{
	if(currQuestion.answered())
	{
		targetPan = currPan - vec(0,48);
		if(currPan.y < 0)
		{
			targetPan.y = targetPan.y += 144;
			currPan.y = currPan.y += 144;
		}

		timePanning = 0;
		yCurrQuestion = yCurrQuestion - 6;
		if(yCurrQuestion < 0)
		{
			yCurrQuestion += 18;
		}
		newQuestion = Question(0,yCurrQuestion);
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
		currStreak += correct;
		totalCorrect += correct;
		totalAsked++;
	}

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
			lastQuestion.clean();
			lastQuestion = currQuestion;
			currQuestion = newQuestion;
			panning = 0;
		}
	}
}

Result Questioner::cleanGame()
{
	Result result = Result(longestStreak, totalAsked, totalCorrect);
	myGameDrawer.paintGameOver(myCube, totalCorrect, longestStreak);
	return result;
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

void Questioner::removeOperator(int mySide)
{
	int opPos = 1;
	if(mySide == RIGHT)
	{
		opPos = 2;
	}

	currQuestion.printOperator(opPos);
}

Int2 doPanning(Int2 targetPan, int timetaken)
{
	float panningPropTimeLeft = (TIME_TO_SCROLL - timetaken) / (float) TIME_TO_SCROLL;
	
	Float2 diffPan = vec((float) 0, panningPropTimeLeft * PIXEL_SCROLL);
	Float2 newPan = targetPan + diffPan;

	myGameDrawer.doPanning(myCube, newPan.round());

	return newPan.round();
}