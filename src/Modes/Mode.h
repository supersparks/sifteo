#include <sifteo,h>
using namespace Sifteo;

class Mode
{
    //an interface containing all the events that we will need

private:
    GameDrawer* myGameDrawer;
    
public:
    virtual void onAccelChange(unsigned int id); /*needed for the menu?*/
    virtual void onNeighbourAdd(unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1);
    virtual void onNeighbourRemove(unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1);
    
    //needed for the menu? also needed for when reults and stats are shown
    //then the user touches to go back to the main menu
    virtual void onTouch(unsigned int id);

    virtual int getMinCubesReq();
    
}