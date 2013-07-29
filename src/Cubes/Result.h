#include <sifteo.h>
using namespace Sifteo;

class Result
{
private:
	int myCurrStreak;
	int myTotalCorrect;
	int myExtraTime;

public:
	Result(int currStreak, int totalCorrect, int extraTime);

	int getCurrStreak();
	int getTotalCorrect();
	int getExtraTime();
};