#ifndef ASSEMBLY_INST_H
#define ASSEMBLY_INST_H

#include <iostream>
#include <vector>
#include <string>

#include "Register.h"
#include "Const.h"

class AssemblyInstr
{
private:
	std::vector<Register*> registers;
	std::vector<Const*> consts;
	
public:
	AssemblyInstr(void);
	~AssemblyInstr(void);

	void addRegister( Register* reg);
	void addConst( Const* constant);
	std::vector<Register*> getRegisters() const;
	std::vector<Const*> getConsts() const;
	void show();
};

#endif

