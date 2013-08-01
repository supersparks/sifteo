#include <sifteo.h>
#include "assets.gen.h"
#include "./Modes/Normal.h"
#include "./Modes/Practise.h"
#include "./Modes/Mode.h"
#include "./Modes/PlayGame.h"
#include "./src/GameDrawer.h"

using namespace Sifteo;


static AssetSlot MainSlot = AssetSlot::allocate()
	.bootstrap(GameAssets);

static Metadata M = Metadata()
	.title("First Game")
	.package("com.sparx.operators","1.0")
	.icon(Icon)
	.cubeRange(4);

static AssetLoader loader;
static AssetConfiguration<1> assetConfig;
VideoBuffer gVideo[CUBE_ALLOCATION];

GameDrawer myGameDrawer;
Normal normal = Normal();
Practise practise = Practise();
Mode *currMode;

int continueGame = 1;


void addMoreCubes()
{
	continueGame = 0;
	for (CubeID cube : CubeSet::connected())
    {
    	myGameDrawer.drawConnectCube(cube);
    }
}

void onDisconnect(void *x, unsigned int id)
{
	addMoreCubes(); //sets flag to 0 so that main loop does not call currMode.UpdateTime()
}

void onConnect(void *x, unsigned int id)
{
	auto &vid = gVideo[id];
    vid.initMode(BG0);
    vid.attach(id);
    //vid.bg0.erase(StripeTile);

    CubeSet cubesLeft = CubeSet::connected();
	//if(currMode != NULL)
	{
		int numNeeded = 4;//currMode.getMinCubesReq();
		if(id >= numNeeded -1)
		{
			continueGame = 1;
		}
		else
		{
			int found = 1;
			int i = 0;
			for(CubeID cube : CubeSet::connected())
			{
				if(cube != i)
				{
					found = 0;
				}
				++i;
			}
			if(found)
			{
				continueGame = 1;
			}
		}
	}

	
}

void onNeighbourAdd(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1)
{
	currMode->onNeighbourAdd(x, cube0Id, side0,
                       cube1Id, side1);
}
void onNeighbourRemove(void *x,unsigned int cube0Id, unsigned int side0,
                        unsigned int cube1Id, unsigned int side1)
{
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

void GameDrawer::GameDrawer::drawConnectCube(CubeID cube)
{
	gVideo[cube].bg0.image(vec(0,0),ConnectCube);
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
	gVideo[cube].setMode(BG0_BG1);
}

void GameDrawer::switchToBG0(CubeID cube)
{
	gVideo[cube].setMode(BG0);
}

void GameDrawer::setBG1Mask(CubeID cube)
{
	gVideo[cube].bg1.setMask(BG1Mask::filled(vec(0,1),vec(16,1)));
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

void main()
{
	assetConfig.append(MainSlot, GameAssets);
	loader.init();

    Events::cubeConnect.set(&onConnect);
    Events::cubeDisconnect.set(&onDisconnect);
    Events::cubeTouch.set(&onTouch);

    for (CubeID cube : CubeSet::connected())
    {
    	//LOG("cube = %d\n",(int) cube);
    	onConnect(NULL, cube);
    }

    normal = Normal(&myGameDrawer);
    currMode = &normal;

    Events::neighborAdd.set(&onNeighbourAdd);
    Events::neighborRemove.set(&onNeighbourRemove);

    TimeStep ts;
    int exitLoop = 0;

    while(!exitLoop)
    {
    	//LOG("ts.delta() = %d\n",ts.delta().milliseconds());
    	exitLoop = currMode->updateTime(ts.delta());

    	ts.next();
    	System::paint();
    }

    practise = Practise(&myGameDrawer);
    currMode = &practise;

    Events::neighborAdd.set(&onNeighbourAdd);
    Events::neighborRemove.set(&onNeighbourRemove);
    Events::cubeTouch.set(&onTouch);

    TimeStep ts;
    int exitLoop = 0;

    while(!exitLoop)
    {
    	//LOG("ts.delta() = %d\n",ts.delta().milliseconds());
    	exitLoop = currMode->updateTime(ts.delta());

    	ts.next();
    	System::paint();
    }

}