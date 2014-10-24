#ifndef CONST_H
#define CONST_H

#include <iostream>

class Const
{
private:
	std::string signs;

public:
	Const(std::string signs);
	~Const(void);

	std::string getConst();
};

#endif

