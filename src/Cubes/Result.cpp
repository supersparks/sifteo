#include "Result.h"

Result::Result(int currStreak, int totalCorrect, int extraTime, int totalAsked)
{
	myCurrStreak = currStreak;
	myTotalCorrect = totalCorrect;
	myExtraTime = extraTime;

	myTotalAsked = totalAsked;
}

Result::Result()
{
	myCurrStreak = 0;
	myTotalCorrect = 0;
	myExtraTime = 0;
	myTotalAsked = 0;
}

int Result::getCurrStreak()
{
	return myCurrStreak;
}

int Result::getTotalCorrect()
{
	return myTotalCorrect;
}

int Result::getExtraTime()
{
	return myExtraTime;
}

int Result::getTotalAsked()
{
	return myTotalAsked;
}
