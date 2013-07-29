#include "Result.h"

Result::Result(int currStreak, int totalCorrect, int extraTime)
{
	myCurrStreak = currStreak;
	myTotalCorrect = totalCorrect;
	myExtraTime = extraTime;
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