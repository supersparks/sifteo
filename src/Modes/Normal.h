#include <sifteo.h>
using namespace Sifteo;

//In this mode, there an initial time constraint of 1 minute (tbc)
//with every streak  of 4 (tbc) correct answers, more time is added to the timer
class Normal : PlayGame {
    //TODO: set max cubes to 4 in the constructor

private:
    CubeID[] myCubes;
    GameDrawer* myDrawer;

public:
	Normal(GameDrawer* gameDrawer, CubeID[] cubes);

private:
	void onNeighbourAdd(
	unsigned int cube0Id, unsigned int side0, 
	unsigned int cube1Id, unsigned int side1);

	void onNeighbourRemove(
	unsigned int cube0Id, unsigned int side0, 
	unsigned int cube1Id, unsigned int side1);

}