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
                        unsigned int cube1Id, unsigned int side1);
    virtual void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1);
    virtual void onTouch(void *x, unsigned int id);

    virtual int updateTime(TimeDelta delta) = 0;
    virtual void updateDisconnect(unsigned int id) = 0;
    virtual void updateConnect(unsigned int id) = 0;

    Mode();
    
};

#endif