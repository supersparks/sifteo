#ifndef QUESTION_H
#define QUESTION_H

#include <sifteo.h>
#include "QuestionList.h"
#include ".././GameDrawer.h"
using namespace Sifteo;

class Question
{
private:
	int questionArray[6];
	int xPosFirstOp;
	int xPosSecondOp;
	int yPos;
	int extraSpace;
	int firstOpWritten;
	int secondOpWritten;
	int opsChosen[2];
	int answerTaken;
	int opsLocked;
	int myCube;
	int myScore;
	GameDrawer* myGameDrawer;

public:
	Question(GameDrawer* gameDrawer, CubeID cube, int yWritePosition);
	//Only used on disconnection of questioner cube
	Question(GameDrawer* gameDrawer, CubeID cube, int yWritePosition,
		int* question, int updateCorrect);
	//Used only when initialising lastQuestion to an empty question;
	Question(CubeID cube);
	Question(){};

	void printOperator(int whichOp, int whichPos);
	void removeOperator(int whichPos);
	void clean();
	int answered();
	int wasRight();
	void updateToCorrect();
	int* retrieveQuestion();
	bool equals(const Question& q) const;

private:
	int numDigits(int number);
	void questionSubmitted();

};

#endif