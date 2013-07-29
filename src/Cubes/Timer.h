#ifndef TIMER_H
#define TIMER_H

#include <sifteo.h>
#include ".././GameDrawer.h"
using namespace Sifteo;

class Timer
{

private:
	int imageNumber;
	int endTile;
	TimeTicker ticker;
	int secondsLeft;
	GameDrawer* myGameDrawer;
	CubeID myCube;

public:
	Timer(GameDrawer* gameDrawer, CubeID cubeID);
	Timer(){};
	
	void updateAnimation(TimeDelta delta);
	int gameOver();
	void streakIncrease();
	void updateResults(int currStreak, int totalCorrect);

};

#endif