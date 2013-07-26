#include "Normal.h"

Normal::Normal(GameDrawer* gameDrawer, CubeID[] cubes)
{
	myDrawer = gameDrawer;
	myCubes = cubes;
	Questioner(myDrawer,myCubes[0]);
	Operator(myDrawer,myCubes[1]);
	Operator(myDrawer,myCubes[2]);
	Timer(myDrawer,myCubes[3]);
}