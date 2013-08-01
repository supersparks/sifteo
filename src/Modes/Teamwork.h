#include <sifteo,h>
#include "./../GameDrawer.h"
using namespace Sifteo;

//In this mode, the multiple users work together to get as many points as possible.
//Extra time is added for a streak by all the users.
class Teamwork : PlayGame {
    //TODO: set max cubes to CUBE_ALLOCATION

public:
	Teamwork();
	Teamwork(GameDrawer gameDrawer,int numPlayers);

	void onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
	                unsigned int cube1Id, unsigned int side1);
	void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
	                unsigned int cube1Id, unsigned int side1);
	void onTouch(void *x, unsigned int id);
	    

	int updateTime(TimeDelta delta);

private:
    int combinedStreak;
    GameDrawer myGameDrawer;
    int myNumPlayers;
    int totalAsked;
   	int runSpecificGameComms();
   	int questionerID[myNumPlayers];
	int operatorID[2*myNumPlayers];
};