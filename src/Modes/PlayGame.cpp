#include "PlayGame.h"

PlayGame::PlayGame() : Mode()
{
	 countdown = 1;
	 countdownSecs = 0;
	 startgame = 0;
	 ended = 0;
	 ending = 0;
}

int PlayGame::endGame(TimeDelta delta)
{
	for(int i=0; i < CUBE_ALLOCATION; ++i)
	{
		switch(cubeStates[i])
		{
			case (QUESTIONER) :
				myQuestioners[i]->runGame(delta);
				break;
			case (TIMER) :
				myTimers[i]->updateAnimation(delta);
				break;
			default :
				break;
		}
	}
	return runSpecificGameComms();
}

int PlayGame::updateTime(TimeDelta delta)
{	if(countdown)
	{
		//LOG("Doing countdown\n");
		countdownSecs += delta.seconds();
		//LOG("delta.seconds() = %f\n", delta.seconds());
		if((int) countdownSecs >= 3)
		{
			//LOG("countdownSecs = %f\n", countdownSecs);

			countdown = 0;
			startgame = 1;
			for(int i=0; i < CUBE_ALLOCATION; ++i)
			{
				if(cubeStates[i] == QUESTIONER)
				{
					myQuestioners[i]->countdownOver();
				}
			}
		}
		else
		{
			for(int i=0; i < CUBE_ALLOCATION; ++i)
			{
				if(cubeStates[i] == QUESTIONER)
				{
					myGameDrawer->drawCountdown(i, (int) countdownSecs);
				}
			}
		}
	}

	if(startgame)
	{
		//LOG("Doing startgame\n");
		ending = endGame(delta);
		if(ending)
		{
			startgame = 0;
		}
	}

	//LOG("ended = %d\n",ended);
	if(ended)
	{
		return 1;
	}

 	return 0;
}

void PlayGame::onTouch(void *x, unsigned int id)
{
	//LOG("PlayGame touched \n");
	if(cubeStates[id] == QUESTIONER)
	{
		//LOG("Questioner touched\n");
		if(ending)
		{
			//LOG("Questioner touched at end of game\n");
			ended = 1;
		}
	}
}

void PlayGame::onNeighbourAdd(
void *x,
unsigned int cube0Id, unsigned int side0, 
unsigned int cube1Id, unsigned int side1)
{
	if(!ending)
	{
		int questIndex = cubeStates[cube0Id];
		int operIndex = cubeStates[cube1Id];
		if(questIndex == QUESTIONER && operIndex == OPERATOR)
		{
			if(side0 == RIGHT || side0 == LEFT)
			{
				myOperators[cube1Id]->highlightOperator(side1);
				myQuestioners[cube0Id]->inputOperator(side0, side1);
			}
		}

		questIndex = cubeStates[cube1Id];
		operIndex = cubeStates[cube0Id];
		if(questIndex == QUESTIONER && operIndex == OPERATOR)
		{
			if(side1 == RIGHT || side1 == LEFT)
			{
				myOperators[cube0Id]->highlightOperator(side0);
				myQuestioners[cube1Id]->inputOperator(side1, side0);
			}
		}
	}
}

void PlayGame::onNeighbourRemove(
void *x,
unsigned int cube0Id, unsigned int side0, 
unsigned int cube1Id, unsigned int side1)
{
	if(!ending)
	{
		int questIndex = cubeStates[cube0Id];
		int operIndex = cubeStates[cube1Id];
		if(questIndex == QUESTIONER && operIndex == OPERATOR)
		{
			if(side0 == RIGHT || side0 == LEFT)
			{
				myOperators[cube1Id]->dehighlightOperator(side1);
				myQuestioners[cube0Id]->removeOperator(side0);
			}
		}

		questIndex = cubeStates[cube1Id];
		operIndex = cubeStates[cube0Id];
		if(questIndex == QUESTIONER && operIndex == OPERATOR)
		{
			if(side1 == RIGHT || side1 == LEFT)
			{
				myOperators[cube0Id]->dehighlightOperator(side0);
				myQuestioners[cube1Id]->removeOperator(side1);
			}
		}
	}
}

void PlayGame::updateDisconnect(unsigned int id)
{
	//LOG("CUBE: %d has disconnected\n",id);
	
	int cubeReplace = cubeStates[id];

	int i=0;
	while(cubeStates[i] != CONNECTED && i < CUBE_ALLOCATION)
	{
		++i;
	}
	if(i < CUBE_ALLOCATION)
	{
		cubeStates[i] = (CubeState) cubeReplace;
		cubeStates[id] = NOT_CONNECTED;
		switch(cubeReplace)
		{
			case (QUESTIONER) :
			{
				myQuestioners[i] = myQuestioners[id];
				myQuestioners[i]->repaintNewCube(i);
				break;
			}
			case (OPERATOR) :
			{
				myOperators[i] = myOperators[id];
				myOperators[i]->repaintNewCube(i);
				break;
			}
			case (TIMER) :
			{
				myTimers[i] = myTimers[id];
				myTimers[i]->repaintNewCube(i);
				break;
			}
			default :
			{
				break;
			}
		}
	}
	else
	{
		switch(cubeStates[id])
		{
			case(QUESTIONER) :
			{
				cubeStates[id] = QUESTIONER_NEEDED;
				break;
			}
			case(OPERATOR) :
			{
				cubeStates[id] = OPERATOR_NEEDED;
				break;
			}
			case(TIMER) :
			{
				cubeStates[id] = TIMER_NEEDED;
				break;
			}
			default :
				break;
		}
	}
}

void PlayGame::updateConnect(unsigned int id)
{
	//LOG("CUBE: %d has connected\n",id);

	int i=0;
	while(cubeStates[i] != QUESTIONER_NEEDED &&
		cubeStates[i] != OPERATOR_NEEDED &&
		cubeStates[i] != TIMER_NEEDED &&
		i < CUBE_ALLOCATION)
	{
		++i;
	}
	if(i < CUBE_ALLOCATION)
	{
		switch (cubeStates[i])
		{
			case (QUESTIONER_NEEDED) :
			{
				myQuestioners[id] = myQuestioners[i];
				if(!countdown)
				{
					myQuestioners[id]->repaintNewCube(id);
				}
				cubeStates[i] = NOT_CONNECTED;
				cubeStates[id] = QUESTIONER;
				break;
			}
			case (OPERATOR_NEEDED) :
			{
				myOperators[id] = myOperators[i];
				myOperators[id]->repaintNewCube(id);
				cubeStates[i] = NOT_CONNECTED;
				cubeStates[id] = OPERATOR;
				break;
			}
			case (TIMER_NEEDED) :
			{
				myTimers[id] = myTimers[i];
				myTimers[id]->repaintNewCube(id);
				cubeStates[i] = NOT_CONNECTED;
				cubeStates[id] = TIMER;
				break;
			}
			default :
			{
				break;
			}
		}
	}
	//else Error
}

int PlayGame::findIndex(CubeID* myArray, int member)
{
	int i=0;
	while(i < arraysize(myArray))
	{
		if(myArray[i] == member)
		{
			return i;
		}
		++i;
	}
	return -1;
}