#include "Register.h"


Register::Register(std::string name)
{
	this->name = name;
}


Register::~Register(void)
{
}


std::string Register::getName()
{
	return this->name;
}