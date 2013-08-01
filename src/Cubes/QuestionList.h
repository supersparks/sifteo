#ifndef QUESTIONLIST_H
#define QUESTIONLIST_H

#include <sifteo.h>
#include ".././GameDrawer.h"
using namespace Sifteo;

class QuestionList {
    //contains a private static const variable with all the questions and answers
private:
    QuestionList();
    static int questions[407];
    static int numQuestions;
    
public:
	static int getQuestion();
    
};

#endif