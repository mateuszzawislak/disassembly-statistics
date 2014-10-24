#ifndef HEX_SIGN_H
#define HEX_SIGN_H

#include <iostream>

#define HEX_BUFFER_SIZE 2

class HexSign
{
private:
	std::string hex;

public:
	HexSign(void);
	~HexSign(void);

	void setHex(std::string hex);
	std::string getHex();
};

#endif
