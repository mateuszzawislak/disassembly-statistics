#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
#include <vector>
#include "FirstRow.h"
#include "NextRow.h"
#include "HexSign.h"

class Instruction
{
public:
	FirstRow* firstRow;
	std::vector<NextRow*> nextRows;

public:
	Instruction(FirstRow* firstRow);
	~Instruction(void);
	void addNextRow(NextRow* row);
	void show();
	std::vector<HexSign*> getHexes();
};

#endif

