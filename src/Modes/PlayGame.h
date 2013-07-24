#include <sifteo,h>
using namespace Sifteo;

class PlayGame : Mode {
    //constructor for playGame should have a pointer to an instance of
    //VidBuffControl as a parameter
    
private:
    VidBuffControl myVidBuffControl;
    int MAX_CUBES;
    //to keep track of the cubes in the game;
    Cube[] gameCubes;
    
    double timeLeft;
    
    //this is at the beginning of the game - a countdown of when
    //the user starts to play
    double timeUntilStart;
    
public:
    void startGame();
    
    //this is passed a delta from the main method
    //controls the start and end of the game
    //updates timeUntilStart and timeLeft
    void updateTime();
    
    //getScore and streak from questioner
    //display results
    //then go back to the main menu (wait for a touch)
    void endGame();

private:
    virtual void bringUpStats();
    
}