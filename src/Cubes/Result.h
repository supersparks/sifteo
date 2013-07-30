#ifndef RESULT_H
#define RESULT_H

#include <sifteo.h>
#include ".././GameDrawer.h"
using namespace Sifteo;

class Result
{
private:
	int myCurrStreak;
	int myTotalCorrect;
	int myExtraTime;

	int myTotalAsked;

public:
	Result(int currStreak, int totalCorrect, int extraTime, int totalAsked);

	int getCurrStreak();
	int getTotalCorrect();
	int getExtraTime();

	int getTotalAsked();
};

#endif