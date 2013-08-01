#ifndef QUESTIONER_H
#define QUESTIONER_H

#include <sifteo.h>
#include ".././GameDrawer.h"
#include "Question.h"
#include "Result.h"
#define TIME_TO_SCROLL 600
#define TIME_TO_CORRECT 500
#define PIXEL_SCROLL 48
#define FIRST_QUESTION_HEIGHT 4
using namespace Sifteo;

static StoredObject s_HighScore(255);
static StoredObject s_LongestStreak(254);
static StoredObject s_TotalAsked(253);
    
class Questioner{

private:
    int currStreak;
    int totalCorrect;
    int totalAsked;
    int longestStreak;
    int extraTime;

    Question currQuestion;
    Question prevQuestion;
    Question newQuestion;

    CubeID myCube;
    GameDrawer* myGameDrawer;

    int yCurrQuestion;

    Int2 currPan;
    Int2 targetPan;

    int timePanning;
    int panning;
    int corrQuestAns;


public:
    Questioner(GameDrawer * gameDrawer, CubeID cubeID);
    Questioner(){};

    void countdownOver();

    void inputOperator(int mySide,int operSide);
    void removeOperator(unsigned int mySide);

    void runGame(TimeDelta myDelta);
    Result questionUpdate();

    void repaintNewCube(unsigned int cube);
    void cleanGame();

private:
    Int2 doPanning(Int2 targetPan, int timetaken);
    void initStoredObjects();
    
};

#endif