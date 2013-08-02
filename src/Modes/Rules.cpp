#include "Rules.h"

Rules::Rules() : Mode()
{
}

Rules::Rules(GameDrawer* gameDrawer) : Mode()
{
	end = 0;
	myGameDrawer = gameDrawer;
	Questioner::initStoredObjects();

	int i = 0;
	for(int i=0; i < 4; ++i)
    {
    	myGameDrawer->printRules(i, i);
    }
}

int Rules::updateTime(TimeDelta delta){ return end; }


void Rules::onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
            unsigned int cube1Id, unsigned int side1){}
void Rules::onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
                    unsigned int cube1Id, unsigned int side1){}

void Rules::onTouch(void *x, unsigned int id)
{ 
	end  = 1;
	for(int i=1; i < 4; ++i)
	{
		myGameDrawer->paintBlack(i);
	}
}

void Rules::updateDisconnect(unsigned int id){}
void Rules::updateConnect(unsigned int id){}

