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
    int startgame;

    
    double timeLeft;
    
    //this is at the beginning of the game - a countdown of when
    //the user starts to play
    double timeUntilStart;

    //getScore and streak from questioner
    //display results
    //then go back to the main menu (wait for a touch)
    int endGame(TimeDelta delta);

    virtual int runSpecificGameComms();
    
public:
    //this is passed a delta from the main method
    //controls the start and end of the game
    //updates timeUntilStart and timeLeft
    void updateTime(TimeDelta delta);
    


private:
    
}