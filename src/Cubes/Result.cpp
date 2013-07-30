#include "Result.h"

Result::Result(int currStreak, int totalCorrect, int extraTime, int totalAsked)
{
	myCurrStreak = currStreak;
	myTotalCorrect = totalCorrect;
	myExtraTime = extraTime;

	myTotalAsked = totalAsked;
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