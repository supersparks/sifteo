#include <sifteo.h>
#include "./../GameDrawer.h"
#include "PlayGame.h"
using namespace Sifteo;

//In this mode, the multiple users work together to get as many points as possible.
//Extra time is added for a streak by all the users.
class Teamwork : public PlayGame {
    //TODO: set max cubes to CUBE_ALLOCATION

public:
	Teamwork();
	Teamwork(GameDrawer* gameDrawer,int numPlayers);

private:
    int combinedStreak;
    GameDrawer* myGameDrawer;
    int myNumPlayers;
    int totalAsked;
   	int runSpecificGameComms();

   	//used in runSpecificGameComms but could be adapted and used 
   	//higher up in PlayGame
   	int questionerID[CUBE_ALLOCATION];
	int operatorID[CUBE_ALLOCATION];
	int timerID = 0;
};