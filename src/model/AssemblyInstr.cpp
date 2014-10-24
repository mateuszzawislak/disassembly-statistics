#include "AssemblyInstr.h"


AssemblyInstr::AssemblyInstr(void)
{
	registers.reserve(1);
}


AssemblyInstr::~AssemblyInstr(void)
{
	this->consts.clear();
	this->registers.clear();
}

void AssemblyInstr::addRegister(Register* reg)
{
	this->registers.push_back(reg);
}

void AssemblyInstr::addConst(Const* constant)
{
	this->consts.push_back(constant);
}

std::vector<Register*> AssemblyInstr::getRegisters() const
{
	return this->registers;
}

std::vector<Const*> AssemblyInstr::getConsts() const
{
	return this->consts;
}

void AssemblyInstr::show()
{
	std::cout<< std::endl << "Assembly registers: ";
	for(int i=0 ; i<registers.size() ; ++i)
		std::cout<< registers.at(i)->getName() << " " ;

	std::cout<< std::endl << "Assembly const: ";
	for (int i = 0 ; i <consts.size() ; ++i)
		std::cout<< consts.at(i)->getConst() << " " ;

	std::cout<< std::endl;
}
