#include <sifteo/menu.h>
#include "assets.gen.h"
using namespace Sifteo;

class Globals {
	// Static Globals
public:
struct MenuItem gItems[5] = { {&IconRules, &LabelRules}, {&IconProf, &LabelProf}, {&IconMult, &LabelMult}, {&IconSing, &LabelSing}, {NULL,NULL}}; 
struct MenuItem sItems[4] = { {&IconPrac, &LabelPrac}, {&IconComp, &LabelComp}, {&IconBack, &LabelBack}, {NULL,NULL} };
struct MenuItem mItems[4] = { {&IconComp, &LabelComp}, {&IconCoop, &LabelCoop}, {&IconBack, &LabelBack}, {NULL,NULL} };
struct MenuItem cItems[5] = { {&IconNum2, &LabelComp}, {&IconNum3, &LabelCoop}, {&IconNum4, &LabelBack},{&IconBack, &LabelBack}, {NULL,NULL} };
struct MenuAssets gAssets = {&BgTile, &Footer, &LabelEmpty, {&Tip0, &Tip1, &Tip2, NULL}};

};