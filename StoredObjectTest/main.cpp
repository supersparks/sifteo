#include <sifteo.h>
#include <sifteo/menu.h>

using namespace Sifteo;


static Metadata M = Metadata()
    .title("Menu SDK Demo")
    .package("com.sifteo.sdk.menudemo", "1.0.0")
    .cubeRange(1);

static VideoBuffer vid;
static StoredObject totalTouchCount(255);

unsigned size = sizeof(int);

void onTouch(void *x, unsigned int id)
{
	int temp = 0;
	totalTouchCount.readObject(temp,0);
	temp += 1;
	totalTouchCount.writeObject(temp);
}

void main()
{

	void* buff;
	if (totalTouchCount.readObject(buff,0) <= 0)
	{
	   //no data has been saved previously
	   totalTouchCount.writeObject(0);
       LOG("\ntotalTouchCount has been written to\n");

	} else {
        LOG("\ntotalTouchCount hasn't been written to\n");
    }

    Colormap colourList;
    colourList.setEGA();
    vid.setMode(SOLID_MODE);
    vid.colormap[0].set(colourList[1].get());

    Events::cubeTouch.set(&onTouch);

    while(1)
    {
        System::paint();
        int temp = 0;
        totalTouchCount.readObject(temp,0);
        LOG("%d \n",temp);
    }

}