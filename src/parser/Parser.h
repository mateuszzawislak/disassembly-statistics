#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>

#include "Tokenizer.h"
#include "../model/Instruction.h"
#include "../model/Row.h"
#include "../model/NextRow.h"
#include "../model/FirstRow.h"
#include "../model/AssemblyInstr.h"
#include "../model/HexSign.h"
#include "../statistics/Statistics.h"

class Parser
{
private:
	Tokenizer* tokenizer;
	std::set<std::string> registers;
	std::set<std::string> registersPrefixes;
	std::set<std::string> sizes;
	std::set<std::string> opcodes;

	//init functions
	void initRegisters();
	void initOpcodes();
	void initSizeWords();
	void initRegistersPrefixes();

	Statistics* buildStats(std::vector<Instruction*> instructions);

	// parsing functions ...
	Row* line();
	FirstRow* firstRow();
	NextRow* nextRow();
	std::vector<HexSign*> hex();
	std::string hexSign();
	std::string opcode();

	bool containsRegisterPrefix(std::string token);
	bool address(FirstRow* firstRow);
	bool assembly(FirstRow* firstRow);
	bool isSign16(char c);
	bool isOpcodePrefix(std::string opcode);
	bool registry(AssemblyInstr* assembly);
	bool aloneRegistry(AssemblyInstr* assembly);
	bool firstRegistry(AssemblyInstr* assembly);
	bool constant(AssemblyInstr* assembly);
	bool sizeDirective(AssemblyInstr* assembly);
	bool offset(AssemblyInstr* assembly);
	bool offsetRegister(AssemblyInstr* assembly);
	bool offsetConst(AssemblyInstr* assembly);
	bool jmpArg(AssemblyInstr* assembly);

public:
	Parser(std::string fileName);
	~Parser(void);

	Statistics* parse();
};

#endif
