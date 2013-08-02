#include "Timer.h"

Timer::Timer(GameDrawer* gameDrawer, CubeID cubeID, int IsPractise)
{
	myGameDrawer = gameDrawer;
	myCube = cubeID;
	isPractise = IsPractise;

	imageNumber = 8;
	endTile = 15;
	ticker = TimeTicker(1);
	secondsLeft = 60;

	myGameDrawer->switchToBG0_BG1(myCube);
	myGameDrawer->drawTimerBackground(myCube);
	myGameDrawer->setBG1Mask(myCube);
	myGameDrawer->drawTimeBar(myCube);
	myGameDrawer->drawUpdatedResults(myCube, 0, 0);
}

Timer::Timer()
{
	//LOG("EMPTY CONTRUCTOR FOR TIMER\n");
}

void Timer::repaintNewCube(unsigned int cube)
{
	myCube = cube;
	myGameDrawer->switchToBG0_BG1(myCube);
	myGameDrawer->drawTimerBackground(myCube);
	myGameDrawer->setBG1Mask(myCube);

	myGameDrawer->drawTimeBar(myCube);
	for(int i=15; i > endTile; --i)
	{
		myGameDrawer->drawBlankTimeBar(myCube, vec(i,1));
	}
	myGameDrawer->drawTimeBarPartial(myCube, vec(endTile,1),imageNumber);
	myGameDrawer->drawUpdatedResults(myCube, 0, 0);
}

void Timer::updateAnimation(TimeDelta delta)
{
	int tickCount = ticker.tick( delta );

	if(!isPractise)
	{
		secondsLeft -= tickCount;
	}

	int pixelsLeft = (112 * secondsLeft) / 60;
	int newEndTile = 1 + (pixelsLeft / 8);
	imageNumber = 8 - (pixelsLeft % 8);

	if(pixelsLeft > 112)
	{
		myGameDrawer->drawTimeBarPartial(myCube, vec(14,1),0);

		if(pixelsLeft > 112 + 8)
		{
			myGameDrawer->drawTimeBarPartial(myCube, vec(15,1),0);
		}
		else
		{
			myGameDrawer->drawTimeBarPartial(myCube, vec(15,1),imageNumber);
		}
	}
	else
	{
		myGameDrawer->drawTimeBarPartial(myCube, vec(newEndTile,1),imageNumber);

		if(newEndTile < endTile)
		{
			myGameDrawer->drawBlankTimeBar(myCube, vec(endTile,1));
			endTile = newEndTile;
		}
	}
}

int Timer::gameOver()
{
	if (!secondsLeft)
	{
		myGameDrawer->clearBG1Mask(myCube);
		myGameDrawer->switchToBG0(myCube);
		myGameDrawer->paintBlack(myCube);
	}
	return !secondsLeft;
}

void Timer::streakIncrease()
{

	secondsLeft += 5;
	int pixelsLeft = (112 * secondsLeft) / 60;
	int newEndTile = 1 + (pixelsLeft / 8);
	imageNumber = 8 - (pixelsLeft % 8);
	for(int i = endTile; i < newEndTile; ++i)
	{
		myGameDrawer->drawTimeBarPartial(myCube, vec(i,1),0);
	}
	endTile = newEndTile;
	myGameDrawer->drawTimeBarPartial(myCube, vec(endTile,1),imageNumber);
}

void Timer::updateResults(int currStreak, int totalCorrect)
{
	myGameDrawer->drawUpdatedResults(myCube, currStreak, totalCorrect);
}