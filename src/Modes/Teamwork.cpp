#include "Teamwork.h"

Teamwork::Teamwork(){}

Teamwork::Teamwork(GameDrawer* gameDrawer, int numPlayers)
{
	int cubesRequired = numPlayers*3+1;
	System::setCubeRange(cubesRequired);
	myGameDrawer = gameDrawer;
	myNumPlayers = numPlayers;

	int i = 0;
	for(CubeID cube : CubeSet::connected())
    {
    	cubeStates[i] = CONNECTED;
    	++i;
    }

    i = 0;
    while(cubeStates[i])
    {
    	if (i==0)
    	{
        	myTimers[i] = Timer(myGameDrawer,i,0);
    		cubeStates[i] = TIMER;
    		timerID = i;
    	} else if (i<myNumPlayers+1)
    	{
    		myQuestioners[i-1] = Questioner(myGameDrawer,i);
 	   		cubeStates[i] = QUESTIONER;
 	   		questionerID[i-1] = i;
 	   	} else if (i<myNumPlayers*3+1) 
 	   	{
 	   		myOperators[i-myNumPlayers-1] = Operator(myGameDrawer,i);
 	   		cubeStates[i] = OPERATOR;
 	   		operatorID[i-myNumPlayers-1] = i;
 	   	} else if (i<CUBE_ALLOCATION)
 	   	{
 	   		//flush all others as not connected
    	//because choosing not to constantly
    	//update these values manually
 	   		cubeStates[i] = NOT_CONNECTED;
 	   	}
 	   	i++;
    }


	//PRECONDITION: there are enough cubes to have numPlayers playing
	int numCubes = CubeSet::connected().count();
	ASSERT(numCubes >= 3*numPlayers + 1);


	//note that the number of questioner cubes is equal to the number of players
	totalAsked = 0;
	combinedStreak = 0;

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

