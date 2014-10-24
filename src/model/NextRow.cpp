#include "NextRow.h"

NextRow::NextRow(void)
{

}

NextRow::~NextRow(void)
{
	this->hexes.clear();
}

void NextRow::addHex(HexSign* hex)
{
	this->hexes.push_back(hex);
}

Row::RowType NextRow::getType()
{
	return Row::NEXT_ROW;
}

void NextRow::setHexes(std::vector<HexSign*> hexes)
{
	this->hexes = hexes;
}

std::vector<HexSign*> NextRow::getHexes()
{
	return this->hexes;
}