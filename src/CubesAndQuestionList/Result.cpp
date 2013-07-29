#include "Result.h"

Result::Result(int longestStreak, int totalAsked, int totalCorrect)
{
	myLongestStreak = longestStreak;
	myTotalAsked = totalAsked;
	myTotalCorrect = totalCorrect;
}

int Result::getLongestStreak()
{
	return myLongestStreak;
}

int Result::getTotalAsked()
{
	return myTotalAsked;
}

int Result::getTotalCorrect()
{
	return myTotalCorrect;
}