#ifndef PLAYGAME_H
#define PLAYGAME_H

#include <sifteo.h>
#include ".././GameDrawer.h"
#include "Mode.h"
#include ".././Cubes/Questioner.h"
#include ".././Cubes/Operator.h"
#include ".././Cubes/Timer.h"
using namespace Sifteo;

class PlayGame : public Mode {
    //constructor for playGame should have a pointer to an instance of
    //VidBuffControl as a parameter
    
protected:
    PlayGame();

protected:
    GameDrawer* myGameDrawer;
    
    CubeID* questionerCubes;
    CubeID* operatorCubes;
    CubeID* timerCubes;
    Questioner* myQuestioners;
    Operator* myOperators;
    Timer* myTimers;

private:
    int countdown;
    int countdownSecs;
    int startgame;

    int endGame(TimeDelta delta);

    virtual int runSpecificGameComms();

    int findIndex(CubeID* myArray, int member);

public:
    void onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1);
    void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1);

    int updateTime(TimeDelta delta);
};

#endif