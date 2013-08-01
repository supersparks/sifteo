#ifndef SHOWSTAT_H
#define SHOWSTAT_H

#include <sifteo.h>
#include <sifteo/menu.h>
#include "./../GameDrawer.h"
#include "./../Modes/Mode.h"
#include "assets.gen.h"
#include "./../Cubes/Questioner.h"

using namespace Sifteo;

class ShowStat : public Mode
{
	private:
		Menu statsMenu;
		GameDrawer* myGameDrawer;
		bool end;

	public:
		struct MenuItem gItems[5] = { {&IconSing, &LabelSing}, {&IconMult, &LabelMult}, {&IconStats, &LabelStats}, {&IconRules, &LabelRules}, {NULL,NULL}}; 
		struct MenuAssets gAssets = {&BgTile, &Footer, &LabelEmpty, {&Tip0, &Tip1, &Tip2, NULL}};

		ShowStat();
	    ShowStat(GameDrawer* gameDrawer);

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