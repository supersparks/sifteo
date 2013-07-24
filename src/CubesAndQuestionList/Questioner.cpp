#include "Questioner.h"


Questioner::Questioner(CubeID cubeId){
	Cube(cubeId);
	leftOp = 0;
	rightOp = 0;
	left = FALSE;
	right = FALSE;
	streak = 0;
	totalCorrect = 0;


}


Questioner::addNeighbour(int mySide,int neighbourSide){

	if (mySide==Cube.LEFT){
		leftOp = neighbourSide;
		left = TRUE;

		//TODO: need operator to apear in the questioner cube

	} else if (mySide==Cube.RIGHT){
		rightOp = neighbourSide;
		right = TRUE;

		//TODO: need operator to apear in the questioner cube

	}

	if (left&&right){
		//question is ready to be marked.
		resolveQuestion();
	}

}


Questioner::resolveQuestion(){
	//check leftOp and rightOp with currQuestion
	
}