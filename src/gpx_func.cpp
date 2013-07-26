static VideoBuffer gVideo[CUBE_ALLOCATION];


void onDisconnect(void *x, unsigned int id)
{
	addMoreCubes(); //sets flag to 0 so that main loop does not call currMode.UpdateTime()
}

void onConnect(void *x, unsigned int id)
{
	auto &vid = gVideo[id];
    vid.initMode(BG0);
    vid.attach(id);
    vid.bg0.erase(StripeTile);

    CubeSet cubesLeft = CubeSet::connected();
	if(currMode != NULL)
	{
		int numNeeded = currMode.getMinCubesReq();
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

//Mode currMode = Normal();

void addMoreCubes()
{
	continueGame = 0;
	for (CubeID cube : CubeSet::connected())
    {
    	myGameDrawer.drawConnectCube(cube);
    }
}