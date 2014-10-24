#include "Instruction.h"


Instruction::Instruction(FirstRow* firstRow)
{
	this->firstRow = firstRow;
}


Instruction::~Instruction(void)
{
	delete firstRow;
	this->nextRows.clear();
}

void Instruction::addNextRow(NextRow* row)
{
	this->nextRows.push_back(row);
}

std::vector<HexSign*> Instruction::getHexes()
{
	std::vector<HexSign*> hexes = this->firstRow->getHexes();
	for(int i=0; i<nextRows.size(); ++i)
	{
		std::vector<HexSign*> nextRowHexes = nextRows.at(i)->getHexes();
		hexes.insert( hexes.end(), nextRowHexes.begin(), nextRowHexes.end() );
	}

	return hexes;
}

void Instruction::show()
{
	std::string addr = firstRow->getAddress();
	std::cout << std::endl;
	std::cout << "Instr: addr: " << addr ;
	std::vector<HexSign*> hexes = getHexes();
	std::cout << " hexes: " ;
	for( int i = 0 ; i < hexes.size() ; ++i)
		std::cout << " " << hexes.at(i)->getHex();
	if(firstRow->getAssembly() != NULL)
		firstRow->getAssembly()->show();
}