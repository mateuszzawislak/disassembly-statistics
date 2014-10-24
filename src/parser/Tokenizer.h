#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../model/Line.h"
#include "CheckPoint.h"

class Tokenizer
{
private:
	std::string fileName;
	std::ifstream infile;
	Line* line;

	void readFile();
	std::string replaceAll(std::string& stri, const std::string& from, const std::string& to);
	std::vector<std::string> stringSplit(const std::string &source, const char *delimiter = " ", bool keepEmpty = false);


public:
	Tokenizer(std::string fileName);
	~Tokenizer();
	std::string getCurrentToken();
	void advance();
	void goToNextLine();
	bool existsCurrentLine();
	bool isEndOfLine();
	CheckPoint* getCurrentCheckPoint();
	void rollBackToCheckPoint(CheckPoint* point);
};

#endif

