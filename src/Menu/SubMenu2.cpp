#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
#include "Globals.cpp"
#define COOP 0
#define COMP 1

#define TWOPLAYER 0
#define THREEPLAYER 1
#define BACK 2
using namespace Sifteo;

class SubMenu2
{

private: 
    Menu myMenu;
    int beingUsed;
    VideoBuffer* myVid;
    Globals myGlobals;
    int myGameType;
    int backIndex;


public: 
    SubMenu2(VideoBuffer* vid, int gameType)
    {
        myVid = vid;
        myGameType = gameType;

        int numCubes = CubeSet::connected().count();

        if(gameType == COOP)
        {
            if(numCubes < 7)
            {
                myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.m0Items);
                backIndex = 0;
            }
            else if(numCubes < 10)
            {
                myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.m2Items);
                backIndex = 1;
            }
            else
            {
                myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.m3Items);
                backIndex = 2;
            }
        }
        else
        {
            if(numCubes < 8)
            {
                myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.m0Items);
                backIndex = 0;
            }
            else if(numCubes < 12)
            {
                myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.m2Items);
                backIndex = 1;
            }
            else
            {
                myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.m3Items);
                backIndex = 2;
            }
        }
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

        //LOG("Running Sub Menu 2\n");
        while (myMenu.pollEvent(&e))
        {
            switch (e.type)
            {
                case MENU_ITEM_PRESS:
                    //LOG("PRESS");
                    //myMenu.anchor(e.item);
                    if(e.item == backIndex)
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

        if(myGameType == COOP && e.item != backIndex)
        {
            System::setCubeRange(7);
            return 2 + e.item;
        }
        else if(myGameType == COMP && e.item != backIndex)
        {
            return 4 + e.item;
        }
        else
        {
            return -1;
        }

        //Should never reach here
        return -1;
    }


};