#include <sifteo,h>
using namespace Sifteo;

class Questioner : Cube {

private:
    int leftOp, rightOp;
    int streak;
    int totalCorrect;
    int[] currQuestion;
    int[] prevQuestion;
    bool left,right;
    
public:
    Questioner(Game * game, CubeID cubeID);
    void addNeighbour(int mySide,int neighbourSide); /*not sure about types?*/
    
    //check leftOp and rightOp with currQuestion; update Streak and totalCorrect.
    //Obtain new question then show animation
    void resolveQuestion();
    
}