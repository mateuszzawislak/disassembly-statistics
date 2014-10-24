#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <vector>

class Line
{
private:
	int currentIndex;
	std::vector<std::string> tokens;
public:
	Line(std::vector<std::string> tokens);
	~Line(void);

	std::string getCurrentToken();
	bool isEnd();
	void advance();
	int getCurrentIndex();
	void setCurrentIndex(int index);
};

#endif

