#include <sifteo.h>
#include <sifteo/menu.h>
#include "assets.gen.h"
#include "MainMenu.cpp"

using namespace Sifteo;

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(BetterflowAssets);

static VideoBuffer gVideo[CUBE_ALLOCATION];
static AssetLoader loader;
static AssetConfiguration<1> assetConfig;

static Metadata M = Metadata()
    .title("Menu SDK Demo")
    .package("com.sifteo.sdk.menudemo", "1.0.0")
    .icon(Icon)
    .cubeRange(1,CUBE_ALLOCATION);

void onConnect(void *x, unsigned int cube)
{
    loader.start(assetConfig);
    loader.finish();

    auto &vid = gVideo[cube];
    vid.initMode(BG0);
    vid.attach(cube);
    vid.bg0.erase(StripeTile);
}

void main()
{
    assetConfig.append(MainSlot, BetterflowAssets);
    loader.init();

    for (CubeID cube : CubeSet::connected())
    {
        onConnect(NULL, cube);
    }
    Events::cubeConnect.set(&onConnect);

    gVideo[0].setMode(BG0);

    MainMenu gameMenu(&gVideo[0]);

    int colour;
    Colormap colourList;
    colourList.setEGA();

    

    while(1)
    {
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
