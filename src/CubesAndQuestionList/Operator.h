#include <sifteo.h>
using namespace Sifteo;

class Operator{

private:
	CubeID myCube;
	GameDrawer* myDrawer;

public:
	Operator(GameDrawer* gameDrawer, CubeID cubeID);
    void highlightOperator(unsigned int opCubeId, unsigned int quSide,unsigned int opSide);
    void dehighlightOperator(unsigned int opCubeId, unsigned int side);
}