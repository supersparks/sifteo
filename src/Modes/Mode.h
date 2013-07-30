#ifndef MODE_H
#define MODE_H

#include <sifteo.h>
#include ".././GameDrawer.h"
using namespace Sifteo;

class Mode
{
    //an interface containing all the events that we will need

private:
    GameDrawer* myGameDrawer;
    
public:
    //virtual void onAccelChange(unsigned int id); /*needed for the menu?*/
    virtual void onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1) = 0;
    virtual void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1) = 0;
    virtual void onTouch(void *x, unsigned int id) = 0;
    
    //needed for the menu? also needed for when reults and stats are shown
    //then the user touches to go back to the main menu
    //virtual void onTouch(unsigned int id);

    virtual int getMinCubesReq(){return 1;};
    virtual int updateTime(TimeDelta delta) = 0;

    Mode();
    
};

#endif