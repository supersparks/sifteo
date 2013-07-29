#include "PlayGame.h"

PlayGame::PlayGame()
{
	 countdown = 1;
	 countdownSecs = 0;
	 startgame = 0;
}

int PlayGame::endGame(TimeDelta delta)
{
	for(int i=0; i < arraysize(myQuestioners); ++i)
	{
		myQuestioners[i].runGame(delta);
	}
	for(int i=0; i < arraysize(myTimers); ++i)
	{
		myTimers[i].updateAnimation(delta);
	}
	return runSpecificGameComms();
}

int PlayGame::updateTime(TimeDelta delta)
{
	if(countdown)
	{
		countdownSecs += delta.seconds();
		for(int i=0; i < arraysize(questionerCubes); ++i)
		{
			myGameDrawer->drawCountdown(questionerCubes[i], (int) countdownSecs);
		}
		if((int) countdownSecs >= 3)
		{
			countdown = 0;
			startgame = 1;
		}
	}

	if(startgame)
	{
		int ended = endGame(delta);
		if(ended)
		{
			return 1;
		}
	}

	return 0;
}

void PlayGame::onNeighbourAdd(
void *x,
unsigned int cube0Id, unsigned int side0, 
unsigned int cube1Id, unsigned int side1)
{
	int questIndex = findIndex(questionerCubes,cube0Id);
	int operIndex = findIndex(operatorCubes,cube1Id);
	if(questIndex != -1 && operIndex!= -1)
	{
		if(side0 == RIGHT || side0 == LEFT)
		{
			myOperators[operIndex].highlightOperator(side1);
			myQuestioners[questIndex].inputOperator(side0,side1);
		}
	}

	questIndex = findIndex(questionerCubes,cube1Id);
	operIndex = findIndex(operatorCubes,cube0Id);
	if(questIndex != -1 && operIndex!= -1)
	{
		if(side1 == RIGHT || side1 == LEFT)
		{
			myOperators[operIndex].highlightOperator(side0);
			myQuestioners[questIndex].inputOperator(side1,side0);
		}
	}
}

void PlayGame::onNeighbourRemove(
void *x,
unsigned int cube0Id, unsigned int side0, 
unsigned int cube1Id, unsigned int side1)
{
	int questIndex = findIndex(questionerCubes,cube0Id);
	int operIndex = findIndex(operatorCubes,cube1Id);
	if(questIndex != -1 && operIndex!= -1)
	{
		if(side0 == RIGHT || side0 == LEFT)
		{
			myOperators[operIndex].dehighlightOperator(side1);
			myQuestioners[questIndex].removeOperator(side1);
		}
	}

	questIndex = findIndex(questionerCubes,cube1Id);
	operIndex = findIndex(operatorCubes,cube0Id);
	if(questIndex != -1 && operIndex!= -1)
	{
		if(side1 == RIGHT || side1 == LEFT)
		{
			myOperators[operIndex].dehighlightOperator(side0);
			myQuestioners[questIndex].removeOperator(side0);
		}
	}
}

int PlayGame::findIndex(CubeID* myArray, int member)
{
	int i=0;
	while(i < arraysize(myArray))
	{
		if(myArray[i] == member)
		{
			return i;
		}
		++i;
	}
	return -1;
}