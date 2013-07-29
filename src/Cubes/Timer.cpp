#include "Timer.h"

Timer::Timer(GameDrawer* gameDrawer, CubeID cubeID)
{
	myGameDrawer = gameDrawer;
	myCube = cubeID;

	imageNumber = 0;
	endTile = 14;
	ticker = TimeTicker(1);
	secondsLeft = 60;

	myGameDrawer->switchToBG0_BG1(myCube);
	myGameDrawer->drawTimerBackground(myCube);
	myGameDrawer->setBG1Mask(myCube);
	myGameDrawer->drawTimeBar(myCube);

	myGameDrawer->drawBlankTimeBar(myCube, vec(endTile,1));


}

void Timer::updateAnimation(TimeDelta delta)
{
	int tickCount = ticker.tick( delta );
	if (tickCount > 0)
	{
		secondsLeft -= tickCount;

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
}

int Timer::gameOver()
{
	if (!secondsLeft)
	{
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
	for(int i = endTile; i <= newEndTile; ++i)
	{
		myGameDrawer->drawTimeBarPartial(myCube, vec(i,1),0);
	}
	endTile = newEndTile;
}

void Timer::updateResults(int currStreak, int totalCorrect)
{
	myGameDrawer->drawUpdatedResults(myCube, currStreak, totalCorrect);
}