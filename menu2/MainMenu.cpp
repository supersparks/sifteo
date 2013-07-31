#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
#include "SubMenu.cpp"

#define SINGLE_PLAYER 0
#define MULTIPLAYER 1
#define STATS 2
using namespace Sifteo;

class MainMenu
{

private:
    Menu myMenu;
    SubMenu mySubMenu;
    VideoBuffer* myVid;
    Globals myGlobals;

public: 
    MainMenu(VideoBuffer* vid,Globals globals)
{

    myGlobals = globals;
    myVid  = vid;

    myMenu = Menu(*myVid, &globals.gAssets, globals.gItems);
    myMenu.anchor(0);
}

public:
    int runMenu()
    {
        struct MenuEvent e;
        uint8_t item;
        int repeatMenu = 0;

        LOG("Running Main Menu\n");

        if(mySubMenu.inUse())
        {
            int sMenuPick = mySubMenu.runMenu();
            if(sMenuPick != 2)
            {
                return e.item*2 + sMenuPick;
            }
            LOG("Registered pressing Back before loop in Main menu class\n");
        }

        // LOG("About to Enter Main Menu loop\n");
        do
        {
        LOG("Inside the Main Menu loop\n");
        while (myMenu.pollEvent(&e))
        {
            switch (e.type)
            {
                case MENU_ITEM_PRESS:
                    myMenu.anchor(e.item);
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

        if(e.item == 2 || e.item == 3)
        {
            if(e.item == 2)
            {
                mySubMenu = SubMenu(myVid,1,myGlobals);
            }
            else
            {
                mySubMenu = SubMenu(myVid,0,myGlobals);
            }

            int sMenuPick = mySubMenu.runMenu();
            if(sMenuPick == 2)
            {
                //go back to main menu
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
        // //the main menu has 3 items:
        // switch (e.item)
        // {
        //     case (SINGLE_PLAYER):
        //         mySubMenu = SubMenu(myVid,1,myGlobals);
        //         sMenuPick = mySubMenu.runMenu();
        //         if(sMenuPick == -1)
        //         {
        //             //go back to main menu
        //             repeatMenu = 1;
        //         } else 
        //         {
        //             return sMenuPick;
        //         }

        //     case (MULTIPLAYER):
        //         mySubMenu = SubMenu(myVid,1,myGlobals);
        //         sMenuPick = mySubMenu.runMenu();
        //         if(sMenuPick == -1)
        //         {
        //             //go back to main menu
        //             repeatMenu = 1;
        //         } else 
        //         {
        //             return sMenuPick;
        //         }

        //     case (STATS):
        //         return 1;
        // }

        } while(repeatMenu);

    //     //Should never get here
         return -1;
    } 

};