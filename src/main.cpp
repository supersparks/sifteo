#include <sifteo.h>
#include "assets.gen.h"
#include "./Modes/Normal.h"
#include "./Modes/Practise.h"
#include "./Modes/Mode.h"
#include "./Modes/PlayGame.h"
#include "./Modes/ShowStat.h"
#include "./Modes/MultCompetitive.h"
#include "./Modes/Rules.h"
#include "./Modes/Teamwork.h"
#include "./GameDrawer.h"
#include "./Menu/MainMenu.cpp"
#include <sifteo.h>
using namespace Sifteo;

static AssetSlot MainSlot = AssetSlot::allocate()
	.bootstrap(MenuImageAssets);

static Metadata M = Metadata()
	.title("First Game")
	.package("com.sparx.operators","1.0")
	.icon(Icon)
	.cubeRange(1,CUBE_ALLOCATION);

//static AssetLoader loader;
//static AssetConfiguration<1> assetConfig;
VideoBuffer gVideo[CUBE_ALLOCATION];

GameDrawer myGameDrawer;
Normal normal = Normal();
Practise practise = Practise();
ShowStat showStat = ShowStat();
Rules rules = Rules();
Teamwork teamwork = Teamwork();
MultCompetitive multcompetitive = MultCompetitive();

//All other modes instantiated using default constructors
Mode *currMode = NULL;
CubeSet cubes;

void onDisconnect(void *x, unsigned int id)
{
	//LOG("logged disconnect from cube: %d\n",id);
    cubes = CubeSet::connected();
	if(currMode)
	{
		currMode->updateDisconnect(id);
	}
}

void onConnect(void *x, unsigned int id)
{
	//LOG("logged connect from cube: %d\n",id);
	auto &vid = gVideo[id];
    vid.initMode(BG0);
    vid.attach(id);
    vid.bg0.erase(StripeTile);
    cubes = CubeSet::connected();
    if(currMode)
	{
		currMode->updateConnect(id);
	}

}

void onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1)
{
    //LOG("Cube %d was neighboured with cube %d\n",cube0Id, cube1Id);
	currMode->onNeighbourAdd(x, cube0Id, side0,
                       cube1Id, side1);
}
void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1)
{
    //LOG("Cube %d was de-neighboured with cube %d\n",cube0Id, cube1Id);
	currMode->onNeighbourRemove(x, cube0Id, side0,
                       cube1Id, side1);
}
void onTouch(void *x,unsigned int cube)
{
	currMode->onTouch(x, cube);
}




void GameDrawer::drawOpHighlight(CubeID cube, Int2 TopLeft, Int2 OpSize, int Highlight)
{
	gVideo[cube].bg0.image(TopLeft, OpSize, Highlights[Highlight], TopLeft, 0);
}

void GameDrawer::printQuestion(CubeID cube, Int2 TopLeft, String<16> quText)
{
	gVideo[cube].bg0.text(TopLeft, Font, quText, ' ');
}

void GameDrawer::printGreenQuestion(CubeID cube, Int2 TopLeft, String<16> quText)
{
	gVideo[cube].bg0.text(TopLeft, FontGreen, quText, ' ');
}

void GameDrawer::printRedQuestion(CubeID cube, Int2 TopLeft, String<16> quText)
{
	gVideo[cube].bg0.text(TopLeft, FontRed, quText, ' ');
}

void GameDrawer::printOperator(CubeID cube, Int2 TopLeft, int whichOp)
{
	gVideo[cube].bg0.image(TopLeft,OperImages[whichOp] );
}

void GameDrawer::printGreenOperator(CubeID cube, Int2 TopLeft, int whichOp)
{
	gVideo[cube].bg0.image(TopLeft,OperImagesGreen[whichOp] );
}

void GameDrawer::printRedOperator(CubeID cube, Int2 TopLeft, int whichOp)
{
	gVideo[cube].bg0.image(TopLeft,OperImagesRed[whichOp] );
}

void GameDrawer::doPanning(CubeID cube, Int2 Pan)
{
    //LOG("Cube %d will be set to pan at (%d,%d)\n",(int) cube, Pan.x, Pan.y);
	gVideo[cube].bg0.setPanning(Pan);
}

void GameDrawer::paintGameOver(CubeID cube, int Score, int longestStreak)
{
	gVideo[cube].bg0.setPanning(vec(0,0));
	gVideo[cube].bg0.image(vec(0,0), GameOver);
	String<9> score;
	score << Score;
	String<9> lStreak;
	lStreak << longestStreak;
	gVideo[cube].bg0.text(vec(8,8),Font2, score, ' ');
	gVideo[cube].bg0.text(vec(8,12),Font2, lStreak, ' ');
}

void GameDrawer::paintGameOverTeamwork(CubeID cube, int Score, int longestStreak, int teamTotalCorrect)
{
    gVideo[cube].bg0.setPanning(vec(0,0));
    gVideo[cube].bg0.image(vec(0,0), GameOverTeam);
    String<9> score;
    score << Score;
    String<9> lStreak;
    lStreak << longestStreak;
    String<9> teamScore;
    teamScore << teamTotalCorrect;
    gVideo[cube].bg0.text(vec(11,7),Font2, teamScore, ' ');
    gVideo[cube].bg0.text(vec(11,10),Font2, score, ' ');
    gVideo[cube].bg0.text(vec(11,13),Font2, lStreak, ' ');
}

void GameDrawer::paintGameOverMultiplayer(CubeID cube, int Score, int longestStreak, int winner, int winnerScore)
{
    gVideo[cube].bg0.setPanning(vec(0,0));
    gVideo[cube].bg0.image(vec(0,0), GameOverMult[winner]);
    String<9> score;
    score << Score;
    String<9> lStreak;
    lStreak << longestStreak;
    String<9> winScore;
    winScore << winnerScore;
    gVideo[cube].bg0.text(vec(12,7),Font2, winScore, ' ');
    gVideo[cube].bg0.text(vec(12,10),Font2, score, ' ');
    gVideo[cube].bg0.text(vec(12,13),Font2, lStreak, ' ');
}

void GameDrawer::drawWhichPlayer(CubeID cube, int playerNum)
{
    gVideo[cube].bg0.image(vec(0,0), PlayerNumbers[playerNum]);
}


void GameDrawer::drawCountdown(CubeID cube, int CountdownSecs)
{
	//LOG("real cube id is = %d\n",(unsigned int)gVideo[cube].cube());
	gVideo[cube].bg0.image(vec(0,0),Countdown[CountdownSecs]);
}

void GameDrawer::drawOperatorBackground(CubeID cube)
{
	gVideo[cube].bg0.image(vec(0,0),Highlights[0]);
}

void GameDrawer::drawTimerBackground(CubeID cube)
{
	//LOG("real cube id is = %d\n",(unsigned int)gVideo[cube].cube());
	gVideo[cube].bg0.image(vec(0,0),TimerBackground);
}

void GameDrawer::drawQuestionerBackground(CubeID cube)
{
	gVideo[cube].bg0.image(vec(0,0),QuestionerBackground);
}

void GameDrawer::switchToBG0_BG1(CubeID cube)
{
    gVideo[cube].initMode(BG0_BG1);
	gVideo[cube].attach(cube);
}

void GameDrawer::switchToBG0(CubeID cube)
{
	gVideo[cube].initMode(BG0);
    gVideo[cube].attach(cube);
}

void GameDrawer::setBG1Mask(CubeID cube)
{
	gVideo[cube].bg1.setMask(BG1Mask::filled(vec(0,1),vec(16,1)));
}

void GameDrawer::clearBG1Mask(CubeID cube)
{
    gVideo[cube].bg1.eraseMask();
}

void GameDrawer::drawTimeBar(CubeID cube)
{
	gVideo[cube].bg1.image(vec(0,1),Timebar);
}

void GameDrawer::drawTimeBarPartial(CubeID cube, Int2 TopLeft, int index)
{
	gVideo[cube].bg1.image(TopLeft,TimebarAnim[index]);
}

void GameDrawer::drawBlankTimeBar(CubeID cube, Int2 TopLeft)
{
	gVideo[cube].bg1.image(TopLeft, pixelsWhite);
}

void GameDrawer::paintBlack(CubeID cube)
{
	gVideo[cube].bg0.image(vec(0,0), BlackImage);
}

void GameDrawer::playCorrect()
{
    //Sifteo::AudioChannel(0).play(MusicCorrect, AudioChannel::ONCE);
    //Sifteo::AudioChannel(1).play(MusicCorrect, AudioChannel::ONCE);
    //Sifteo::AudioChannel(2).play(MusicCorrect, AudioChannel::ONCE);
    //Sifteo::AudioChannel(3).play(MusicCorrect, AudioChannel::ONCE);
    AudioTracker::play(MusicCorrect);
}

void GameDrawer::playWrong()
{
    //Sifteo::AudioChannel(4).play(MusicWrong, AudioChannel::ONCE);
    //Sifteo::AudioChannel(5).play(MusicWrong, AudioChannel::ONCE);
    //Sifteo::AudioChannel(6).play(MusicWrong, AudioChannel::ONCE);
    //Sifteo::AudioChannel(7).play(MusicWrong, AudioChannel::ONCE);
    AudioTracker::play(MusicWrong);
}

void GameDrawer::drawUpdatedResults(CubeID cube, int currStreak, int totalCorrect)
{
	if(!currStreak)
	{
		for(int i=10; i < 13; ++i)
		{
			gVideo[cube].bg0.image(vec(i,12), pixelsWhite);
			gVideo[cube].bg0.image(vec(i,13), pixelsWhite);
		}
	}
	String<9> score;
	score << totalCorrect;

	gVideo[cube].bg0.text(vec(10,8),Font, score, ' ');

	String<9> cStreak;
	cStreak << currStreak;
	gVideo[cube].bg0.text(vec(10,12),Font, cStreak, ' ');


}


void GameDrawer::printStats(int hscore,int lstreak,int totalAsked)
{
    gVideo[0].bg0.image(vec(0,0),StatsBackground);

    String<9> str_hscore;
    String<9> str_lstreak;
    String<9> str_totalAsked;

    str_hscore << hscore;
    str_lstreak << lstreak;
    str_totalAsked << totalAsked;

    gVideo[0].bg0.text(vec(13,3),Font,str_hscore, ' ');
    gVideo[0].bg0.text(vec(13,6),Font,str_lstreak, ' ');
    gVideo[0].bg0.text(vec(13,12),Font,str_totalAsked, ' ');

}

void GameDrawer::printRules(CubeID cube, int image)
{
    gVideo[cube].bg0.image(vec(0,0),RulesBackground[image]);
}

void main()
{
    Sifteo::ScopedAssetLoader assetLoader;

    assetLoader.init();
    
    ASSERT(MenuImageAssets.isInstalled(CubeSet::connected()));

    Events::cubeConnect.set(&onConnect);
    Events::cubeDisconnect.set(&onDisconnect);

    for (CubeID cube : CubeSet::connected())
    {
    	//LOG("cube = %d\n",(int) cube);
    	onConnect(NULL, cube);
    }

    //LOG("I am about to create a game menu\n");

    MainMenu gameMenu(&gVideo[0]);

    while(1)
    {

        currMode = NULL;
        

        cubes = CubeSet::connected();

        /* Only needed if we do not want to bootstrap
        MenuImageAssets anymore.*/
        AssetConfiguration<1> assetConfig;

        if(!MenuImageAssets.isInstalled(cubes))
        {
            assetConfig.append(MainSlot, MenuImageAssets);
            assetLoader.start(assetConfig, cubes);
            while (!assetLoader.isComplete())
            {
                System::paint();
            }
        }

        for(CubeID cube : cubes)
        {
            gVideo[cube].bg0.erase(StripeTile);
        }

        //LOG("About to run menu\n");

    	int modeChosen = gameMenu.runMenu();

        //LOG("Just run menu\n");

        if(!GameAssets.isInstalled(cubes))
        {
            assetConfig.append(MainSlot, GameAssets);
            assetLoader.start(assetConfig, cubes);
            for(CubeID cube : cubes)
            {
                gVideo[cube].initMode(BG0_ROM);
                gVideo[cube].attach(cube);
                gVideo[cube].bg0rom.fill(vec(0,0),vec(16,16),BG0ROMDrawable::SOLID_BG);
                gVideo[cube].bg0rom.text(vec(1,1), "Loading...", BG0ROMDrawable::BLACK);
            }
            while (!assetLoader.isComplete())
            {
                System::paint();
            }
            for(CubeID cube : cubes)
            {
                gVideo[cube].initMode(BG0);
                gVideo[cube].attach(cube);
            }
        }

        Events::cubeTouch.set(&onTouch);
        Events::neighborAdd.set(&onNeighbourAdd);
        Events::neighborRemove.set(&onNeighbourRemove);
        //LOG("Loading done\n");

    	//Do mode
    	switch(modeChosen)
    	{
    		case(0) :
    		{
    			normal = Normal(&myGameDrawer);
    			currMode = &normal;
    			break;
    		}
    		case(1) :
    		{
    			practise = Practise(&myGameDrawer);
                currMode = &practise;
    			break;
    		}
    		case(2) :
    		{
    			teamwork = Teamwork(&myGameDrawer, 2);
                currMode = &teamwork;
    			break;
    		}
    		case(3) :
    		{
    			teamwork = Teamwork(&myGameDrawer, 3);
                currMode = &teamwork;
    			break;
    		}
    		case(4) :
    		{
    			multcompetitive = MultCompetitive(&myGameDrawer, 2);
                currMode = &multcompetitive;
    			break;
    		}
    		case(5) :
    		{
    			multcompetitive = MultCompetitive(&myGameDrawer, 3);
                currMode = &multcompetitive;
    			break;
    		}
    		case(6) :
    		{
    			showStat = ShowStat(&myGameDrawer);
                currMode = &showStat;
    			break;
    		}
    		case(7) :
    		{
                rules = Rules(&myGameDrawer);
                currMode = &rules;
                break;
    		}
    		default :
    		{
    			break;
    		}
    	}
    	

    	TimeStep ts;
		int exitLoop = 0;

		while(!exitLoop)
	    {
	    	//LOG("ts.delta() = %d\n",ts.delta().milliseconds());
	    	exitLoop = currMode->updateTime(ts.delta());

	    	ts.next();
	    	System::paint();
	    }

        //Do menu
        Events::cubeTouch.unset();
        Events::neighborAdd.unset();
        Events::neighborRemove.unset();
        System::setCubeRange(1,CUBE_ALLOCATION);
        //LOG("events unset\n");

        //LOG("Finished mode\n");
    }
}
