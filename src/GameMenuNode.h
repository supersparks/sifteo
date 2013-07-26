#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
using namespace Sifteo;

class GameMenuNode 
{

static struct MenuItem mainMenuItems[] = { {&MenuImages[1], &LabelRules}, {&MenuImages[2], &LabelProf}, {&MenuImages[3], &LabelSing} }; 
static struct MenuItem singlePlayerItems[] = { {&MenuImages_single[1], &LabelPrac}, {&MenuImages_single[2], &LabelComp}, {&IconBack, &LabelBack}, {NULL,NULL} };
static struct MenuItem multiplayerPickModeItems[] = { {&MenuImages_multi[1], &LabelComp}, {&MenuImages_multi[2], &LabelCoop}, {&IconBack, &LabelBack}, {NULL,NULL} };
static struct MenuItem multiplayerNumPlayersItems[] = { {&MenuImages_multi_num[1], &LabelComp}, {&MenuImages_multi_num[2], &LabelCoop}, {&MenuImages_multi_num[3], &LabelCoop}, {&IconBack, &LabelBack}, {NULL,NULL} };
static struct MenuAssets gAssets = {&BgTile, &Footer, &LabelEmpty, {&Tip0, &Tip1, &Tip2, NULL}};

public:
	static int MAIN_MENU = 0;
	static int SINGLE_PLAYER_MENU = 1;
	static int MULTIPLAYER_MENU = 2;
	static int TEAMWORK_SELECT_NUM = 3;
	static int COMPETITIVE_SELECIT_NUM = 4;

private:
	bool hasChild;
	bool hasParent;
	bool isBeingUsed;
	bool keepLooping;

	Menu myMenu;
	GameMenuNode mySubMenu;
	Cubeid menuCube;

	int menuSet;
	int numItems;

	//INVARIANT: hasChild => 
	//				(mySubmenu.inUse() => isBeingUsed)

public:
	GameMenuNode(VideoBuffer vid,CubeID cube,int menuSet);
	GameMenuNode();

	int runMenu();
	bool inUse();

private:
	bool menuLogic(int item);


}