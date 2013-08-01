#include "Teamwork.h"

Teamwork::Teamwork(){}

Teamwork::Teamwork(GameDrawer* gameDrawer, int numPlayers)
{
	int cubesRequired = numPlayers*3+1;
	System::setCubeRange(cubesRequired);

	int i = 0;
	for(CubeID cube : CubeSet::connected())
    {
    	cubeStates[i] = CONNECTED;
    	++i;
    }

    i = 0;
    while(!cubeStates[i])
    {
    	if (i==0)
    	{
        	myTimers[i] = Timer(myGameDrawer,i,0);
    		cubeStates[i] = TIMER;
    	} else if (i<myNumPlayers+1)
    	{
    		myQuestioners[i-1] = Questioner(myGameDrawer,i);
 	   		cubeStates[i-1] = QUESTIONER;
 	   	} else if (i<myNumPlayers*3+1) 
 	   	{
 	   		myOperators[i-myNumPlayers-1] = Operator(myGameDrawer,i);
 	   		cubeStates[i-myNumPlayers-1] = OPERATOR;
 	   	}
 	   i++;
    }


    //flush all others as not connected
    //because choosing not to constantly
    //update these values manually
    i=cubesRequired;
    while(i < CUBE_ALLOCATION)
    {
    	cubeStates[i] = NOT_CONNECTED;
    	++i;
    }

	//PRECONDITION: there are enough cubes to have numPlayers playing
	int numCubes = CubeSet::connected().count();
	ASSERT(numCubes >= 3*numPlayers + 1);

	myGameDrawer = gameDrawer;
	myNumPlayers = numPlayers;
	//note that the number of questioner cubes is equal to the number of players
	totalAsked = 0;
	combinedStreak = 0;

	//find out which cubes are the questioners,timers or questioners
	i++;
	int qCount=0;
	int oCount=0;
	while(i<CUBE_ALLOCATION)
	{
		if(cubeStates[i] == QUESTIONER)
		{
			questionerID[qCount] = i;
			qCount++;
		} else if (cubeStates[i] ==OPERATOR)
		{
			operatorID[oCount] = i;
		} else if (cubeStates[i] == TIMER)
		{
			timerID = i;
		}

		i++;
	}
	
	LOG("oCount = %d\n",oCount);
	LOG("qCount = %d\n",qCount);
	LOG("myNumPlayers = %d\n",myNumPlayers);
	ASSERT(oCount+1==myNumPlayers*2);
	ASSERT(qCount+1==myNumPlayers);

}

//returns 1 when the game has ended
//returns 0 if the game needs to keep looping
//assumes that this method is called at a raster rate than 
//the rate of the players combined can answer questions
int Teamwork::runSpecificGameComms()
{

	Result currResult[CUBE_ALLOCATION];
	//get most recent result from each questioner
	for (int i=0;i<myNumPlayers;i++)
	{
		currResult[i] = myQuestioners[questionerID[i]].questionUpdate();
	}

	int combinedGain =0;
	int streakIncrement = 0;
	int broken = 1;
	int temp = 0;
	for(int i=0;i<myNumPlayers;i++)
	{
		temp = currResult[i].getCurrStreak();
		broken *= temp;
		combinedGain += temp;
	}
	streakIncrement = (broken==0)? 0 : combinedGain;
	combinedStreak += streakIncrement;

	//if we need extra time then increase the time as needed on the timer
	if (streakIncrement>=5)
	{
		myTimers[timerID].streakIncrease();
	}

	int newTotalAsked=0;
	//update totalAsked,currStreak and totalCorrect on the timer
	for(int i=0;i<myNumPlayers;i++)
	{
		newTotalAsked += currResult[i].getTotalAsked();
	}

	if( newTotalAsked >0)
	{
		totalAsked += newTotalAsked;
		myTimers[timerID].updateResults(combinedStreak, totalAsked);
	}

	//if it is game over then clean game from all the cubes
	if(myTimers[timerID].gameOver())
	{
		//clean game on all the questioners
		for(int i=0;i<myNumPlayers;i++)
		{
			myQuestioners[questionerID[i]].cleanGame();
		}

		//cleangame on all the operators
		for(int i=0;i<myNumPlayers;i++)
		{
			myOperators[operatorID[i]].cleanGame();
		}
		
		return 1;
	}

	return 0;
}

