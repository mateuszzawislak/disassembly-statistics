#include "CheckPoint.h"


CheckPoint::CheckPoint(int linePosition, int tokenInLineIndex)
{
	this->linePosition = linePosition;
	this->tokenInLineIndex = tokenInLineIndex;
}


CheckPoint::~CheckPoint(void)
{
}

int CheckPoint::getLinePosition()
{
	return this->linePosition;
}

int CheckPoint::getTokenInLineIndex()
{
	return this->tokenInLineIndex;
}
