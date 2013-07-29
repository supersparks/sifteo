#include <sifteo.h>
using namespace Sifteo;

class Operator{

private:
	CubeID myCube;

public:
	Operator(GameDrawer* gameDrawer, CubeID cubeID);
    void highlightOperator(unsigned int opCubeId, unsigned int quSide,unsigned int opSide);
    void dehighlightOperator(unsigned int opCubeId, unsigned int side);
    void cleanGame();
}