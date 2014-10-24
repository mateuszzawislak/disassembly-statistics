#ifndef FIRSTROW_H
#define FIRSTROW_H

#include <iostream>
#include <vector>

#include "AssemblyInstr.h"
#include "HexSign.h"
#include "Row.h"

class FirstRow : public Row
{
private:
	std::string address;
	std::vector<HexSign*> hexes;
	std::string opcode;
	AssemblyInstr* assembly;

public:
	FirstRow(void);
	FirstRow(std::string opcode, std::string address);
	~FirstRow(void);

	void addAssembly(AssemblyInstr* assemby);
	void addHex(HexSign* hex);
	void setHexes(std::vector<HexSign*> hexes);
	void setOpcode(std::string opcode);
	void setAddress(std::string);
	std::vector<HexSign*> getHexes();
	std::string getOpcode();
	AssemblyInstr* getAssembly();
	std::string getAddress();

	Row::RowType getType();
};

#endif

