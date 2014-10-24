#include "HexSign.h"


HexSign::HexSign(void)
{
}


HexSign::~HexSign(void)
{
}

void HexSign::setHex(std::string hex)
{
		this->hex=hex;
}

std::string HexSign::getHex()
{
	return this->hex;
}
