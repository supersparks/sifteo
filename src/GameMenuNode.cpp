#include "GameMenuNode.h"

GameMenuNode::GameMenuNode(VideoBuffer vid,CubeID cube,int menuSet)
{
	menuCube = cube;
	this.menuSet = menuSet;
	isBeingUsed = true;

	switch (menuSet)
	{
		case GameMenuNode::MAIN_MENU;
			hasChild = 1;
			hasParent = 0;
			keepLooping = 1;
			myMenu(vid,&gAssets,mainMenuItems);
			numItems = 3;
			break;
		case GameMenuNode::SINGLE_PLAYER_MENU;
			hasChild = 1;
			hasParent = 1;
			keepLooping = 0;
			myMenu(vid,&gAssets,singlePlayerItems);
			numItems = 3;
			break;
		case GameMenuNode::MULTIPLAYER_MENU;
			hasChild = 1;
			hasParent = 1;
			keepLooping = 1;
			myMenu(vid,&gAssets,multiplayerPickModeItems);
			numItems = 3;
			break;
		case GameMenuNode::TEAMWORK_SELECT_NUM;
			hasChild = 0;
			hasParent = 1;
			keepLooping = 0;
			myMenu(vid,&gAssets,multiplayerNumPlayersItems);
			numItems = 4;
			break;
		case GameMenuNode::COMPETITVE_SELECT_NUM;
			hasChild = 0;
			hasParent = 1;
			keepLooping = 0;
			myMenu(vid,&gAssets,multiplayerNumPlayersItems);
			numItems = 4;
			break;
	}
}


GameMenuNode::GameMenuNode()
{
	isBeingUsed = false;
}

//returns whether it's parent menu should keep looping
bool GameMenuMode::runMenu()
{
    struct MenuEvent e;
    uint8_t item;

  	if (hasChild && mySubMenu.inUse())
    {
    	int sMenuPick = mySubMenu.runMenu();

    	//if they didn't press go back then keep running this menu;
    	if (sMenuPick != -1){
    		return true;
    	}
    }

    do
    {
	    while (myMenu.pollEvent(&e))
	    {
	        switch (e.type)
	        {
	            case MENU_ITEM_PRESS:
	                myMenu.anchor(e.item);
	                if(e.item == 2)
	                {
	                    isBeingUsed = 0;
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

	    //LOGIC FOR THE MENUS GOES HERE
	    keepLooping = menuLogic(e.item);

    } while (keepLooping);

    return keepLooping;
}



bool GameMenuNode::inUse()
{
	return isBeingUsed;
}

//returns whether it's parent menu should keep looping
bool GameMenuNode::menuLogic(int item)
{
	bool keepLoopingRes = 1;

	//cases for current menuset
	switch (menuSet)
	{
		case GameMenuNode::MAIN_MENU;
			switch (item)
			{
				case 1;
					//single player
					LOG("SINGLE PLAYER");
					keepLoopingRes = 1
					break;
				case 2;
					//multiplayer
					LOG("MULTIPLAYER");
					keepLoopingRes = 1
					break;
				case 3;
					//show stats
					LOG("SHOW STATS");
					keepLoopingRes = 1
					break;
				case 4;
					//show rules
					LOG("SHOW RULES");
					keepLoopingRes = 1
					break;
			}
			break;
		case GameMenuNode::SINGLE_PLAYER_MENU;
			switch (item)
			{
				case 1;
					//single player normal
					LOG("NORMAL");
					keepLoopingRes = 0;
					break;
				case 2;
					//single player practise
					LOG("PRACTISE");
					keepLoopingRes = 0;
					break;
				case 3;
					//move back to main menu
					keepLoopingRes = 1;
					break;
			}
			break;
		case GameMenuNode::MULTIPLAYER_MENU;
			switch (item)
			{
				case 1;
					//move to GameMenuNode::TEAMWORK_SELECT_NUM
					mySubMenu = GameMenu(menuCube,GameMenuNode::TEAMWORK_SELECT_NUM);
					keepLoopingRes = mySubMenu.runMenu();
					break;
				case 2;
					//move to GameMenuNode::COMPETITIVE_SELECT_NUM
					mySubMenu = GameMenu(menuCube,GameMenuNode::COMPETITIVE_SELECT_NUM);
					keepLoopingRes = mySubMenu.runMenu();
					break;
				case 3;
					//move back to main menu
					keepLoopingRes =1;
					break;
			}
			break;
		case GameMenuNode::TEAMWORK_SELECT_NUM;
			switch (item)
			{
				case 1;
					//2 player teamwork game
					keepLoopingRes = 0;
					break;
				case 2;
					//3 player teamwork game
					keepLoopingRes = 0;
					break;
				case 3;
					//4 player teamwork game
					keepLoopingRes = 0;
					break;
				case 4;
					//back to multiplayer menu
					keppLoopingRes = 1;
					break;
			}
			break;
		case GameMenuNode::COMPETITVE_SELECT_NUM;
			switch (item)
			{
				case 1;
					//2 player competitive game
					keepLoopingRes = 0;
					break;
				case 2;
					//3 player competitive game
					keepLoopingRes = 0;
					break;
				case 3;
					//4 player competitive game
					keepLoopingRes = 0;
					break;
				case 4;
					//back to multiplayer menu
					keepLoopingRes = 1;
					break;
			}
			break;s
	}

	return keepLoopingRes;
}
