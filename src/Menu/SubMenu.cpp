#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
#include "SubMenu2.cpp"
#define NORMAL 0
#define PRACTISE 1
#define COOP 0
#define COMP 1
#define BACK 2

#define SINGLE 0
#define MULTI 1
using namespace Sifteo;

class SubMenu
{

private: 
    Menu myMenu;
    SubMenu2 mySubMenu;
    int beingUsed;
    VideoBuffer* myVid;
    Globals myGlobals;
    int myGameType;



public: 
    SubMenu(VideoBuffer* vid, int gameType)
    {
        myVid = vid;
        myGameType = gameType;
        //Single Player
        if(myGameType == SINGLE)
        {
            myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.sItems);
            myMenu.anchor(0);
        }
        else
        {
            //Multiplayer
            myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.mItems);
            myMenu.anchor(0);
        }
        beingUsed = 1;
    }
    
public:
    SubMenu()
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
        int repeatMenu = 0;

        /*if(mySubMenu.inUse())
        {
            int sMenuPick = mySubMenu.runMenu();
            if(sMenuPick != -1)
            {
                return sMenuPick;
            }
            //LOG("Registered pressing Back before loop in Main menu class\n");
        }*/

        do
        {
            //LOG("Running Sub Menu\n");
            while (myMenu.pollEvent(&e))
            {
                switch (e.type)
                {
                    case MENU_ITEM_PRESS:
                        myMenu.anchor(e.item);
                        if(e.item == BACK)
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


            //new layer of menus
            if((e.item == COOP || e.item == COMP) && myGameType == MULTI)
            {
                if(e.item == COOP)
                {
                    mySubMenu = SubMenu2(myVid,0);
                }
                else if (e.item == COMP)
                {
                    mySubMenu = SubMenu2(myVid,1);
                }

                int sMenuPick = mySubMenu.runMenu();
                if(sMenuPick == -1)
                {
                    //LOG("Registered pressing Back to SubMenu class\n");
                    repeatMenu = 1;
                }
                else 
                {
                    return sMenuPick;
                }
            }
            else if((e.item == NORMAL || e.item == PRACTISE) && myGameType == SINGLE)
            {
                System::setCubeRange(4);
                if(e.item == NORMAL)
                {
                    return 0;
                }
                else if(e.item == PRACTISE)
                {
                    return 1;
                }
            }
            else
            {
                return -1;
            }
        } while(repeatMenu);

        //Should never get down here
        return -2;
    }



};