#include "QuestionList.h"

int QuestionList::questions[3][6] = {{66,3,13,1,10,69}, {10,2,5,3,8,10}, {12,3,5,3,19,36} };

int QuestionList::numQuestions = 3;

int* QuestionList::getQuestion()
{
	Random r;
	return questions[r.randint(0,numQuestions-1)];
}