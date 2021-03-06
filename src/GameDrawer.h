#ifndef GAMEDRAWER_H
#define GAMEDRAWER_H

#include <sifteo.h>
using namespace Sifteo;

class GameDrawer
{

public:

void drawOpHighlight(CubeID cube, Int2 TopLeft, Int2 OpSize, int Highlight);

void printQuestion(CubeID cube, Int2 TopLeft, String<16> quText);

void printRedQuestion(CubeID cube, Int2 TopLeft, String<16> quText);

void printGreenQuestion(CubeID cube, Int2 TopLeft, String<16> quText);

void printOperator(CubeID cube, Int2 TopLeft, int whichOp);

void printRedOperator(CubeID cube, Int2 TopLeft, int whichOp);

void printGreenOperator(CubeID cube, Int2 TopLeft, int whichOp);

void doPanning(CubeID cube, Int2 Pan);

void paintGameOver(CubeID cube, int Score, int longestStreak);

void paintGameOverTeamwork(CubeID cube, int teamLongestStreak, int longestStreak, int teamTotalCorrect);

void paintGameOverMultiplayer(CubeID cube, int Score, int longestStreak, int winner, int winnerScore);

void drawWhichPlayer(CubeID cube, int playerNum);

void drawCountdown(CubeID cube, int CountdownSecs);

void drawOperatorBackground(CubeID cube);

void drawTimerBackground(CubeID cube);

void drawQuestionerBackground(CubeID cube);

void switchToBG0_BG1(CubeID cube);

void switchToBG0(CubeID cube);

void setBG1Mask(CubeID cube);

void clearBG1Mask(CubeID cube);

void drawTimeBar(CubeID cube);

void drawTimeBarPartial(CubeID cube, Int2 TopLeft, int index);

void drawBlankTimeBar(CubeID cube, Int2 TopLeft);

void paintBlack(CubeID cube);

void drawUpdatedResults(CubeID cube, int currStreak, int totalCorrect);

void playCorrect();

void playWrong();

void printStats(int hscore,int lstreak,int totalAsked);

void printRules(CubeID cube, int image);

};

#endif