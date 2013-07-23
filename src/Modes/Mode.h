#include <sifteo,h>
using namespace Sifteo;

class Mode {
    //an inteface containing all the events that we will need
    
public:
    void onAccelChange(void *x, unsigned int id); /*needed for the menu?*/
    void onNeighbourAdd(void *x,
                        unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1);
    
    //needed for the menu? also needed for when reults and stats are shown
    //then the user touches to go back to the main menu
    void onTouch(void *x,unsigned int id);
    
    void onConnect(void *x, unsigned int id); /*needed when switching to multiplayer?*/
    
}