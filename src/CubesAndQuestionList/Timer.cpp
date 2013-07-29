#include "Timer.h"

Timer::Timer(GameDrawer* gameDrawer, CubeID cubeID)
{
	myGameDrawer = gameDrawer;
	myCube = cubeID;

	imageNumber = 0;
	endTile = 14;
	ticker = TimeTicker(1);
	secondsLeft = 60;

	myGameDrawer.switchToBG0_BG1(myCube);
	myGameDrawer.drawTimerBackground(myCube);
	myGameDrawer.setBG1Mask(myCube);
	myGameDrawer.drawTimeBar(myCube);

	myGameDrawer.drawTimeBarPartial(myCube, vec(endTile), pixelsWhite);


}

void updateAnimation(delta)
{
	int tickCount = ticker.tick( delta );

	if (tickCount > 0)
	{
		secondsLeft -= tickCount;

		int pixelsLeft = (112 * secondsLeft) / 60;
		int newEndTile = 1 + (pixelsLeft / 8);
		imageNumber = 8 - (pixelsLeft % 8);

		if(newEndTile < endTile)
		{
			myGameDrawer.drawBlankTimeBar(myCube, vec(endTile,1));
			endTile = newEndTile;
		}
	}
}

void gameOver()
{
	return !secondsLeft;
}

void streakIncrease()
{
	secondsLeft += 5;
}

//Copy this logic in to stop crash of over 60 seconds

	int frameNum = (endTile*numFrames + 5/timePerFrame);
	endTile = frameNum/numFrames;

	if (endTile>maxTiles) vid.bg1.image(vec(maxTiles+1,1),TimebarAnim[1]);

	frame = umod(frameNum,numFrames);

	vid.bg1.image(vec(0,1),Timebar);

	for (int i=endTile+1;i<maxTiles+1;i++){
		vid.bg1.image(vec(i,1),White_Box);