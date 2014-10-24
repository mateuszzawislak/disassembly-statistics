#include "Line.h"

Line::Line(std::vector<std::string> tokens) : currentIndex(0)
{
	this->tokens = tokens;
}

Line::~Line(void)
{

}

std::string Line::getCurrentToken()
{
	return ( currentIndex ) < tokens.size() ? tokens.at(currentIndex) : "";
}

bool Line::isEnd()
{
	return ( currentIndex ) < tokens.size() ? false : true;
}

void Line::advance()
{
	currentIndex++;
}

int Line::getCurrentIndex()
{
	return this->currentIndex;
}

void Line::setCurrentIndex(int index)
{
	this->currentIndex = index;
}
