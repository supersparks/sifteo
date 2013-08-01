#ifndef RULES_H
#define RULES_H

#include <sifteo.h>
#include <sifteo/menu.h>
#include "./../GameDrawer.h"
#include "./../Modes/Mode.h"
#include "assets.gen.h"
#include "./../Cubes/Questioner.h"

using namespace Sifteo;

class Rules : public Mode
{
	private:
		Menu rulesMenu;
		GameDrawer* myGameDrawer;
		bool end;

	public:
		struct MenuItem gItems[5] = { {&IconSing, &LabelSing}, {&IconMult, &LabelMult}, {&IconStats, &LabelStats}, {&IconRules, &LabelRules}, {NULL,NULL}}; 
		struct MenuAssets gAssets = {&BgTile, &Footer, &LabelEmpty, {&Tip0, &Tip1, &Tip2, NULL}};

		Rules();
	    Rules(GameDrawer* gameDrawer);

	public:

	    void onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
                    unsigned int cube1Id, unsigned int side1);
	    void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
	                        unsigned int cube1Id, unsigned int side1);
	    void onTouch(void *x, unsigned int id);

	    int updateTime(TimeDelta delta);
	    void updateDisconnect(unsigned int id);
    	void updateConnect(unsigned int id);

};

#endif