#include <sifteo,h>
using namespace Sifteo;

class PlayGame : Mode {
    //constructor for playGame should have a pointer to an instance of
    //VidBuffControl as a parameter
    
protected:
    PlayGame();

private:
    GameDrawer myGameDrawer;
    Cube[] questionerCubes;
    Cube[] operatorCubes;
    Cube[] timerCubes;
    Questioner[] myQuestioners;
    Operator[] myOperators;
    Timer[] myTimers;

    int countdown;
    int countdownSecs;
    int startgame;

    int endGame(TimeDelta delta);

    virtual int runSpecificGameComms();
    
public:
    //this is passed a delta from the main method
    //controls the start and end of the game
    //updates timeUntilStart and timeLeft
    void updateTime(TimeDelta delta);

    void PlayGame::onNeighbourAdd(
unsigned int cube0Id, unsigned int side0, 
unsigned int cube1Id, unsigned int side1);

    void PlayGame::onNeighbourRemove(
unsigned int cube0Id, unsigned int side0, 
unsigned int cube1Id, unsigned int side1);
    


private:
    int findIndex(int[] myArray, int member);
}