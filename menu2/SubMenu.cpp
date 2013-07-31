#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
#include "SubMenu2.cpp"
#define NORMAL 0
#define PRACTISE 1
#define TEAM 0
#define COMP 1
#define back 2
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
    SubMenu(VideoBuffer* vid, int gameType, Globals globals)
    {
        myGlobals = globals;
        myVid = vid;
        myGameType = gameType;
        //Single Player
        if(myGameType == 0)
        {
            myMenu = Menu(*myVid,&myGlobals.gAssets, myGlobals.sItems);
            myMenu.anchor(0);
        }
        else
        {
            //myGameType = 1, (Multiplayer)

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

        // if(mySubMenu.inUse())
        // {
        //     int sMenuPick = mySubMenu.runMenu();
        //     if(sMenuPick != 2)
        //     {
        //         return e.item*2 + sMenuPick;
        //     }
        //     LOG("Registered pressing Back before loop in Main menu class\n");
        // }

        do
        {
        LOG("Running Sub Menu\n");
        while (myMenu.pollEvent(&e))
        {
            switch (e.type)
            {
                case MENU_ITEM_PRESS:
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


        //new layer of menus
        if((e.item == 0 || e.item == 1) && myGameType!=0)
        {
            if(e.item == 0 )
            {
                mySubMenu = SubMenu2(myVid,1,myGlobals);
            }
            else if (e.item == 1)
            {
                mySubMenu = SubMenu2(myVid,0,myGlobals);
            }

            int sMenuPick = mySubMenu.runMenu();
            if(sMenuPick == 2)
            {
                LOG("Registered pressing Back to SubMenu class\n");
                repeatMenu = 1;
            }
            else 
            {
                return (e.item * 2) + sMenuPick;
            }

        }
        else
        {
            return e.item;
        }
        // int sMenuPick;
        // switch (myGameType) 
        // {
        //     case (0):
        //         switch (e.item) 
        //         
        //             case (NORMAL):
        //                 return 2;
        //             case (PRACTISE):
        //                 return 3;
        //             case (BACK):
        //                 return -1;
        //         }
        //     case (1):
        //         switch (e.item)
        //         {
        //             case (TEAM):
        //                 mySubMenu = SubMenu2(myVid,1,myGlobals);
        //                 sMenuPick = mySubMenu.runMenu();
        //                 if(sMenuPick == -1)
        //                 {
        //                     repeatMenu = 1;
        //                 }
        //                 else 
        //                 {
        //                     return sMenuPick;
        //                 }

        //             case (COMP):
        //                 mySubMenu = SubMenu2(myVid,0,myGlobals);
        //                 sMenuPick = mySubMenu.runMenu();
        //                 if(sMenuPick == -1)
        //                 {
        //                     repeatMenu = 1;
        //                 }
        //                 else 
        //                 {
        //                     return sMenuPick;
        //                 }
        //             case (BACK):
        //                 return -1;
        //         }
        // }


        } while(repeatMenu);

        return e.item;
    }



};