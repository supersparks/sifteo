#ifndef MULTCOMPETITIVE_H
#define MULTCOMPETITIVE_H

#include <sifteo.h>
#include "PlayGame.h"
#include ".././GameDrawer.h"
using namespace Sifteo;

//In this mode, the multiple users race to get the most points.
//Constant amount of time, and bonus points for long streaks.
class MultCompetitive : public PlayGame {
    //TODO: set max cubes to CUBE_ALLOCATION
    //TODO: make sure that the number of operator cubes
    //is n where n = 3k+ 1 and k is an integer
    
private:
 //No newline at end of file
    GameDrawer* myGameDrawer;

public:
	MultCompetitive();
	MultCompetitive(GameDrawer* gameDrawer,int numPlayers);
	    
	int updateTime(TimeDelta delta);

   	int runSpecificGameComms();

private:
	int showWhichPlayer;
	double showPlayerCountdown;
	Questioner myQuestionerArray[3];
    Operator myOperatorArray[6];
    Timer myTimerArray[3];

	int streaks[3];
    int totalAsked[3];

    Result currResult[3];
	int myNumPlayers;
	int Player_GameOver[3];
};

#endif
