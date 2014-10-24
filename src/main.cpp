#include <stdio.h>
#include <iostream>

#include "parser/Parser.h"
#include "statistics/Statistics.h"

int main(int argc, const char* argv[])
{
	std::string inFile = "", outFile = "";
	bool sortFirstColumn = false;

	if (argc < 5) {
		std::cerr << "Usage is " << argv[0] << " -in <disassembly_file> -out <output_file_name>  [-first] " << std::endl;
		std::cin.get();
		exit(0);
	} else {
		for (int i = 1; i < argc; ++i) {
			std::string currArg = std::string(argv[i]);

			if (!currArg.compare("-in")) {
				inFile = std::string(argv[i + 1]);
			} else if (!currArg.compare("-out")) {
				outFile = std::string(argv[i + 1]);
			} else if(!currArg.compare("-first")) {
				sortFirstColumn = true;
			}
		}
	}

	if(!inFile.compare("") || !outFile.compare("")) {
		std::cerr << " Bad arguments! " << std::endl;
		exit(0);
	}

	std::cout << "\nWelcome in application!\n\n" ;

	Parser parser(inFile);
	Statistics* stats = parser.parse();

	std::cerr << "Parsing done" << std::endl;

	stats->writeIntoFile(outFile, sortFirstColumn);

	//stop...
	std::cin.get();
}