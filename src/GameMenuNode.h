#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
using namespace Sifteo;

class GameMenuNode 
{
private:
	bool hasChild;
	bool hasParent;
	bool isBeingUsed;

	Menu myMenu;
	GameMenuNode mySubMenu;
	Cubeid menuCube;

	int menuSet;

public:
	GameMenuNode(CubeID cube,int menuSet);
	GameMenuNode();

	int runMenu();
	bool inUse();

}