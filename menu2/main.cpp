#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
#include "MainMenu.cpp"

using namespace Sifteo;

static const unsigned gNumCubes = 3;
static VideoBuffer gVideo[gNumCubes];

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(BetterflowAssets);

static Metadata M = Metadata()
    .title("Menu SDK Demo")
    .package("com.sifteo.sdk.menudemo", "1.0.0")
    .icon(Icon)
    .cubeRange(gNumCubes);


static void begin() {
    // Blank screens, attach VideoBuffers
    for(CubeID cube = 0; cube != gNumCubes; ++cube) {
        auto &vid = gVideo[cube];
        vid.initMode(BG0);
        vid.attach(cube);
        vid.bg0.erase(StripeTile);
    }
}


void main()
{
    begin();
    Globals globals;
    gVideo[0].setMode(BG0);
    MainMenu gameMenu(&gVideo[0],globals);
    int colour;
    Colormap colourList;
    colourList.setEGA();

    

    while(1)
    {
        //int STATS = 1;
        //int SP_NORMAL = 2;
        //int SP_PRACTISE = 3;
        //int MP_TEAM = 4 5 or 6;
        //int MP_COMP = 7 8 or 9;

        colour = gameMenu.runMenu();

        gVideo[0].setMode(SOLID_MODE);

        gVideo[0].colormap[0].set(colourList[colour].get());
        System::paint();

        TimeStep ts;
        TimeTicker ticker = TimeTicker(1);
        int tickIncr;
        int tickCount  = 0;
        do
        {
            tickIncr = ticker.tick( ts.delta() );
            ts.next();
            tickCount += tickIncr;
        } while (tickCount < 3);

        gVideo[0].setMode(BG0);
        gVideo[0].bg0.erase(StripeTile);
    }

}
