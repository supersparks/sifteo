#include "QuestionList.h"

QuestionList::getQuestion()
{
	Random r;
	retArray = questions[r.randint(0,numQuestions-1)];
}