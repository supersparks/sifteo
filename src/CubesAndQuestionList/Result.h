#include <sifteo.h>
using namespace Sifteo;

class Result
{
private:
	int myLongestStreak;
	int myTotalAsked;
	int myTotalCorrect;

public:
	Result(int longestStreak, int totalAsked, int totalCorrect);

	int getLongestStreak();
	int getTotalAsked();
	int getTotalCorrect();
};