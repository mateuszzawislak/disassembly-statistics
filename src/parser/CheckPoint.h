#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <iostream>

/**
	klasa reprezentuje punkt kontrolny umozliwaijacy nawroty tokenizera
*/
class CheckPoint
{
private: 
	int linePosition;
	int tokenInLineIndex;
public:
	CheckPoint(int linePosition, int tokenInLineIndex );
	~CheckPoint(void);

	int getLinePosition();
	int getTokenInLineIndex();
};

#endif

