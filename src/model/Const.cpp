#include "Const.h"


Const::Const(std::string signs)
{
	this->signs = signs;
}


Const::~Const(void)
{
}

std::string Const::getConst()
{
	return this->signs;
}