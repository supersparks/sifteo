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
 No newline at end of file
    CubeID* myCubes;


public:
	MultCompetitive();
	MultCompetitive(GameDrawer* gameDrawer,int numPlayers);

	void onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
	                unsigned int cube1Id, unsigned int side1);
	void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
	                unsigned int cube1Id, unsigned int side1);
	void onTouch(void *x, unsigned int id);
	    

	int updateTime(TimeDelta delta);

private:
	int myQuestioner[3];
	int myNumPlayers;
	int streaks[3];
	GameDrawer myGameDrawer;
    int totalAsked[3];
   	int runSpecificGameComms();
   	int questionerID[3];
	int operatorID[2*3];
	int timerID[3];
	int combinedResult;
	int Player1_GameOver;
	int Player2_GameOver;
	int Player3_GameOver;

};

#endif
