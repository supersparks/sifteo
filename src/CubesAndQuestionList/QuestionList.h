#include <sifteo.h>
using namespace Sifteo;

class QuestionList {
    //contains a private static const variable with all the questions and answers
private:
    QuestionList();
    int[] getQuestion();
    
public:
    static QuestionList INSTANCE = new QuestionList();
    
}