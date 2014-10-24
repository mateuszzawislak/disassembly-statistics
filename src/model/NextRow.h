#ifndef NEXT_ROW_H
#define NEXT_ROW_H

#include <iostream>
#include <vector>

#include "HexSign.h"
#include "Row.h"

class NextRow : public Row
{
private:
	std::vector<HexSign*> hexes;

public:
	NextRow(void);
	~NextRow(void);

	void addHex(HexSign* hex);
	Row::RowType getType();
	void setHexes(std::vector<HexSign*> hexes);
	std::vector<HexSign*> getHexes();
};

#endif


