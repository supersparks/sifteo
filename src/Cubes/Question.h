#include <sifteo.h>
using namespace Sifteo;

class Question
{
private:
	int * questionArray;
	int xPosFirstOp;
	int xPosSecondOp;
	int yPos;
	int firstOpWritten;
	int secondOpWritten;
	int opsChosen[2];
	int answerTaken;
	int opsLocked;
	int myCube;
	int myScore;

public:
	Question(GameDrawer gameDrawer, CubeID cube, int yWritePosition);
	//Used only when initialising lastQuestion to an empty question;
	Question();

	void printOperator(int whichOp, int whichPos);
	void removeOperator(int whichPos);
	void clean();
	int answered();
	int wasRight();
	void updateToCorrect();

private:
	int numDigits(int number);
	void questionSubmitted();

};