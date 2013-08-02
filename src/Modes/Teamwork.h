#include <sifteo.h>
#include "./../GameDrawer.h"
#include "PlayGame.h"
using namespace Sifteo;

//In this mode, the multiple users work together to get as many points as possible.
//Extra time is added for a streak by all the users.
class Teamwork : public PlayGame {
    //TODO: set max cubes to CUBE_ALLOCATION

public:
	Teamwork(GameDrawer* gameDrawer,int numPlayers);
    Teamwork();

private:
    int combinedStreak;
    GameDrawer* myGameDrawer;
    int myNumPlayers;
    int totalAsked;
   	int runSpecificGameComms();

    //Streak since any player last got
    //a question wrong
   	int unbrokenStreak[3];
    int playerTotalCorrect[3];
    int playerTotalAsked[3];

    Questioner myQuestionerArray[3];
    Operator myOperatorArray[6];
    Timer myOneTimer;
};