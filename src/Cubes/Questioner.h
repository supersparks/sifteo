#include <sifteo.h>
#define TIME_TO_SCROLL 600
#define TIME_TO_CORRECT 500
#define PIXEL_SCROLL 48
#define FIRST_QUESTION_HEIGHT 4
using namespace Sifteo;

class Questioner{

private:
    int currStreak;
    int totalCorrect;
    int totalAsked;
    int longestStreak;
    int extraTime;

    Question currQuestion;
    Question prevQuestion;

    CubeID myCube;

    int yCurrQuestion;

    Int2 currPan;
    Int2 targetPan;

    int timePanning;
    int panning;
    int corrQuestAns;

    
public:
    Questioner(GameDrawer * gameDrawer, CubeID cubeID);

    void inputOperator(int mySide,int operSide);
    void removeOperator(unsigned int mySide);

    void runGame(TimeDelta myDelta);
    void cleanGame();

private:
    Int2 doPanning(Int2 targetPan, int timetaken);
    
}