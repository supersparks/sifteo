#include "Teamwork.h"

Teamwork::Teamwork(){}

Teamwork::Teamwork(GameDrawer* gameDrawer, int numPlayers)
{
	//PRECONDITION: there are enough cubes to have numPlayers playing
	ASSERT(Cubes::cubesConnected.size()>= 3*numPlayers + 1);

	myGameDrawer = gameDrawer;
	myNumPlayers = numPlayers;
	//note that the number of questioner cubes is equal to the number of players
	totalAsked = 0;
	combinedStreak = 0;

	//find out which cubes are the questioners,timers or questioners
	int i=0;
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
			operatorid[oCount] = i;
		} else if (cubeStates[i] == TIMER)
		{
			timerID = i;
		}

		i++;
	}

	ASSERT(oCount+1==numPlayers*2);
	ASSERT(qCount+1==numPlayers);

	combinedResult = Result(0,0,0,0);

}

//returns 1 when the game has ended
//returns 0 if the game needs to keep looping
int Teamwork::runSpecificGameComms()
{

	Result currResult[numPlayers];
	//get most recent result from each questioner
	for (int i=0;i<numPlayers;i++)
	{
		currResult[i] = myQuestioners[questionerid[i]].questionUpdate;
	}

	//work out combined streak
	//to each questioner:
		//what was the last streak?
		//when was the last streak broken?

	//if we need extra time then increase the time as needed on the timers

	//update totalAsked,currStreak and totalCorrect on the timer

	//if it is game over then clean game from all the cubes
	if(myTimers[timerID].gameOver())
	{
		//clean game on all the questioners
		//cleangame on all the operators
		myQuestioners[i].cleanGame();

		myOperators[k].cleanGame();
		myOperators[l].cleanGame();
		return 1;
	}

	return 0;
}

