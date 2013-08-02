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
	int isPractise;
	int gameEnded;
	GameDrawer* myGameDrawer;
	CubeID myCube;

public:
	Timer(GameDrawer* gameDrawer, CubeID cubeID, int IsPractise);
	Timer();
	
	void updateAnimation(TimeDelta delta);
	int gameOver();
	void streakIncrease();
	void updateResults(int currStreak, int totalCorrect);
	void repaintNewCube(unsigned int cube);

};

#endif