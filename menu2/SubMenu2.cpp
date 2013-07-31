#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
#include "Globals.cpp"
using namespace Sifteo;

class SubMenu2
{

private: 
    Menu myMenu;
    int beingUsed;
    VideoBuffer* myVid;
    Globals myGlobals;
    int myGameType;


public: 
    SubMenu2(VideoBuffer* vid, int gameType, Globals globals)
    {
        myGlobals = globals;
        myVid = vid;
        myGameType = gameType;

        myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.mItems);
        myMenu.anchor(0);

        beingUsed = 1;
    }
    
public:
    SubMenu2()
    {
        beingUsed = 0;
    }

public:
    int inUse()
    {
        return beingUsed;
    }

public:
    int runMenu()
    {
        struct MenuEvent e;
        uint8_t item;

        LOG("Running Sub Menu 2\n");
        while (myMenu.pollEvent(&e))
        {
            switch (e.type)
            {
                case MENU_ITEM_PRESS:
                    LOG("PRESS");
                    myMenu.anchor(e.item);
                    if(e.item == 2)
                    {
                        beingUsed = 0;
                    }
                    break;

                case MENU_EXIT:
                    // this is not possible when pollEvent is used as the condition to the while loop.
                    // NOTE: this event should never have its default handler skipped.
                    ASSERT(false);
                    break;

                case MENU_NEIGHBOR_ADD:
                    break;

                case MENU_NEIGHBOR_REMOVE:
                    break;

                case MENU_ITEM_ARRIVE:
                    item = e.item;
                    break;

                case MENU_ITEM_DEPART:
                    break;

                case MENU_PREPAINT:
                    // do your implementation-specific drawing here
                    // NOTE: this event should never have its default handler skipped.
                    break;

                case MENU_UNEVENTFUL:
                    // this should never happen. if it does, it can/should be ignored.
                    ASSERT(false);
                    break;
            }
            myMenu.performDefault();
        }

        return e.item;
    }


};