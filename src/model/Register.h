#ifndef REGISTER_H
#define REGISTER_H

#include <iostream>

class Register
{
private:
	std::string name;
	
public:
	Register(std::string name);
	~Register(void);
	std::string getName();
};

#endif
