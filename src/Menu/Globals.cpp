#include <sifteo/menu.h>
#include "assets.gen.h"
using namespace Sifteo;

class Globals
{
	// Static Globals
public:
	struct MenuItem gItems[5] = { {&IconSing, &LabelSing}, {&IconMult, &LabelMult}, {&IconStats, &LabelStats}, {&IconRules, &LabelRules}, {NULL,NULL}}; 
	struct MenuItem sItems[4] = { {&IconNorm, &LabelNorm}, {&IconPrac, &LabelPrac}, {&IconBack, &LabelBack}, {NULL,NULL} };
	struct MenuItem mItems[4] = { {&IconCoop, &LabelCoop}, {&IconComp, &LabelComp}, {&IconBack, &LabelBack}, {NULL,NULL} };
	struct MenuItem m3Items[4] = { {&IconNum2, &LabelNumPlayers}, {&IconNum3, &LabelNumPlayers}, {&IconBack, &LabelBack}, {NULL,NULL} };
	struct MenuItem m2Items[3] = { {&IconNum2, &LabelNumPlayers}, {&IconBack, &LabelBack}, {NULL,NULL} };
	struct MenuItem m0Items[2] = { {&IconBack, &LabelBack}, {NULL,NULL} };
	struct MenuAssets gAssets = {&BgTile, &Footer, &LabelEmpty, {&Tip0, &Tip1, &Tip2, NULL}};

};