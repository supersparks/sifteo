#include "ShowStat.h"

ShowStat::ShowStat() : Mode()
{
}

ShowStat::ShowStat(GameDrawer* gameDrawer) : Mode()
{
	end = 0;
	myGameDrawer = gameDrawer;
	Questioner::initStoredObjects();

	int highscore = 0;
	int lStreak =  0;
	int totalAsked;
    Questioner::s_HighScore.readObject(highscore,0);
    Questioner::s_LongestStreak.readObject(lStreak,0);
    Questioner::s_TotalAsked.readObject(totalAsked,0);

    myGameDrawer->printStats(highscore,lStreak,totalAsked);
}

int ShowStat::updateTime(TimeDelta delta){ return end; }


void ShowStat::onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
            unsigned int cube1Id, unsigned int side1){}
void ShowStat::onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
                    unsigned int cube1Id, unsigned int side1){}

void ShowStat::onTouch(void *x, unsigned int id)
{ 
	end  = 1;
}

void ShowStat::updateDisconnect(unsigned int id){}
void ShowStat::updateConnect(unsigned int id){}

