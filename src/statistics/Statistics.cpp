#include "Statistics.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>


Statistics::Statistics()
{

}


Statistics::~Statistics(void)
{
}


void Statistics::addInstructionLength(unsigned instructionLength)
{
	if(instructionsLengths.find(instructionLength) == instructionsLengths.end())
        instructionsLengths[instructionLength] = 1;
    else
        instructionsLengths[instructionLength]++;
}

void Statistics::addConstantLength(unsigned constLength)
{
	if(constantsLenghts.find(constLength) == constantsLenghts.end())
        constantsLenghts[constLength] = 1;
    else
        constantsLenghts[constLength]++;
}

void Statistics::addOpcode(std::string opcode)
{
	if(opcodesCounter.find(opcode) == opcodesCounter.end())
        opcodesCounter[opcode] = 1;
    else
        opcodesCounter[opcode]++;
}

void Statistics::addRegister(std::string reg)
{
	if(registersCounter.find(reg) == registersCounter.end())
        registersCounter[reg] = 1;
    else
        registersCounter[reg]++;
}

template<typename A, typename B>
struct sortFirst {
    bool operator()(const std::pair<A, B> &lhs, const std::pair<A, B> &rhs) {
        return lhs.first > rhs.first;
    }
};

template<typename A, typename B>
struct sortSecond {
    bool operator()(const std::pair<A, B> &lhs, const std::pair<A, B> &rhs) {
        return lhs.second > rhs.second;
    }
};

template<typename A, typename B>
void Statistics::sortAndWrite(const std::map<A, B>& mapToPrint, std::string title, std::ofstream& file, bool sortFirstColumn) {
	std::vector<std::pair<A, B> > mapcopy(mapToPrint.begin(), mapToPrint.end());
	if(sortFirstColumn)
		std::sort(mapcopy.begin(), mapcopy.end(), sortFirst<A, B>());
	else
		std::sort(mapcopy.begin(), mapcopy.end(), sortSecond<A, B>());

	file <<"\n " << title << " \n" <<std::endl;
	for( int i= 0; i<mapcopy.size() ;++i)
	{
		file  << mapcopy.at(i).first << " : " << mapcopy.at(i).second << std::endl;
	}
}


void Statistics::writeIntoFile(std::string fileName, bool sortFirstColumn)
{
	std::ofstream file(fileName.c_str());

    if(file.is_open() == false)
    {
        std::cerr << "Cannot open file " + fileName << std::endl;
    }

	sortAndWrite(instructionsLengths, "Instructions lenths:", file, sortFirstColumn );
	sortAndWrite(constantsLenghts, "Consts lenths:", file, sortFirstColumn );
	sortAndWrite(opcodesCounter, "Used opcodes:", file, sortFirstColumn );
	sortAndWrite(registersCounter, "Used registers:", file, sortFirstColumn );

	file.close();

	std::cout << " Statistics wrote into file " << fileName << std::endl;	
}