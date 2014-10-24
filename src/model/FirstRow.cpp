#include "FirstRow.h"


FirstRow::FirstRow(void)
{
	assembly = NULL;
}


FirstRow::~FirstRow(void)
{
	if( assembly != NULL )
		delete assembly;
	this->hexes.clear();
}

FirstRow::FirstRow(std::string opcode, std::string address)
{
	this->address = address;
	this->opcode = opcode;
}

void FirstRow::addAssembly(AssemblyInstr* assemby)
{
	this->assembly = assemby;
}

void FirstRow::addHex(HexSign* hex)
{
	this->hexes.push_back(hex);
}

Row::RowType FirstRow::getType()
{
	return Row::FIRST_ROW;
}

void FirstRow::setHexes(std::vector<HexSign*> hexes)
{
	this->hexes.swap(hexes);
}

void FirstRow::setOpcode(std::string opcode)
{
	this->opcode = opcode;
}

std::vector<HexSign*> FirstRow::getHexes()
{
	return this->hexes;
}

std::string FirstRow::getOpcode()
{
	return this->opcode;
}

AssemblyInstr* FirstRow::getAssembly()
{
	return this->assembly;
}
std::string FirstRow::getAddress()
{
	return this->address;
}


void FirstRow::setAddress(std::string address)
{
	this->address = address;
}