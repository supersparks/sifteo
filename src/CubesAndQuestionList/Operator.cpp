#include "Operator.h"

Operator::Operator(GameDrawer* gameDrawer, CubeID cubeID)
{
	myCube = cubeID;
	myDrawer = gameDrawer;
	myDrawer.drawOperatorBackground(myCube);
}

void Operator::highlightOperator(unsigned int opSide)
{
	CubeID cube(opCubeId);

	Int2 OpPosition = vec(0,0);

	switch(opSide)
	{
		case(0) :
			OpPosition = vec(5,0);
			break;
		case(1) :
			OpPosition = vec(0,5);
			break;
		case(2) :
			OpPosition = vec(5,10);
			break;
		case(3) :
			OpPosition = vec(10,5);
			break;
	}
	myDrawer.drawOpHighlight(myCube, OpPosition, vec(6,6), 1);
}

void Operator::dehighlightOperator(unsigned int opSide)
{
	CubeID cube(opCubeId);

	Int2 OpPosition = vec(0,0);

	switch(opSide)
	{
		case(0) :
			OpPosition = vec(5,0);
			break;
		case(1) :
			OpPosition = vec(0,5);
			break;
		case(2) :
			OpPosition = vec(5,10);
			break;
		case(3) :
			OpPosition = vec(10,5);
			break;
	}
	myDrawer.drawOpHighlight(myCube, OpPosition,vec(6,6), 0);
}