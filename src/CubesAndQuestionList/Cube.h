#include <sifteo,h>
using namespace Sifteo;


class Cube {
    //just an empty base class from which Questioner and Operator inherit from
private:
    CubeID myCubeId;
    Cube(CubeID cubeID);
public:
    static int LEFT = 0;
    static int RIGHT = 1;
    static int TOP = 2;
    static int BOTTOM = 3;

    static int ADD = RIGHT;
    static int SUBTRACT = LEFT;
    static int MULTIPLY = TOP;
    static int DIVIDE = BOTTOM;
    
}