#ifndef STATISTICS_H
#define STATISTICS_H

#include <map>
#include <fstream>
#include <string>

#include "../model/Const.h"
#include "../model/Register.h"


/**
	klasa do budowania statystyk
*/
class Statistics
{
private:
	std::string fileName;

	std::map<unsigned, unsigned> instructionsLengths;
	std::map<unsigned, unsigned> constantsLenghts;
	std::map<std::string, unsigned> opcodesCounter;
	std::map<std::string, unsigned> registersCounter;
	template<typename A, typename B>
	void sortAndWrite(const std::map<A, B>& mapToPrint, std::string title, std::ofstream& file, bool sortFirstColumn);
    
public:
	Statistics(void);
	~Statistics(void);

	void addInstructionLength(unsigned length);
	void addConstantLength(unsigned length);
	void addOpcode(std::string opcode);
	void addRegister(std::string reg);
	void writeIntoFile(std::string fileName, bool sortFirstColumn);
};

#endif

