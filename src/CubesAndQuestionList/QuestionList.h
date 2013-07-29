#include <sifteo.h>
using namespace Sifteo;

class QuestionList {
    //contains a private static const variable with all the questions and answers
private:
    QuestionList();
    int[] getQuestion();
    const int questions[3][6] = {{66,3,13,1,10,69}, {10,2,5,3,8,10}, {12,3,5,3,19,36} };
    int numQuestions = 3;
    
public:
    static QuestionList INSTANCE = new QuestionList();
    
}