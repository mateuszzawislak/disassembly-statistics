#include "Tokenizer.h"

Tokenizer::Tokenizer(std::string fileName)
{
	std::cout<< " Opening file " << fileName <<std::endl;

	try{

		this->fileName = fileName;
		infile.open(fileName.c_str());
		if( !infile.is_open())
		{
			std::string message = "File " + fileName + " can not be open!";
			throw std::exception(message.c_str());
		}

		goToNextLine();
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

}

Tokenizer::~Tokenizer()
{

}

void Tokenizer::readFile()
{

}

std::string Tokenizer::getCurrentToken()
{
	return line->getCurrentToken();
}

void Tokenizer::advance()
{
	line->advance();
}


std::string Tokenizer::replaceAll(std::string& stri, const std::string& from, const std::string& to) {
	std::string str = stri;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }

	return str;
}

std::vector<std::string> Tokenizer::stringSplit(const std::string &source, const char *delimiter, bool keepEmpty)
{
    std::vector<std::string> results;

    size_t prev = 0;
    size_t next = 0;

    while ((next = source.find_first_of(delimiter, prev)) != std::string::npos)
    {
        if (keepEmpty || (next - prev != 0))
        {
            results.push_back(source.substr(prev, next - prev));
        }
        prev = next + 1;
    }

    if (prev < source.size())
    {
        results.push_back(source.substr(prev));
    }

    return results;
}

void Tokenizer::goToNextLine()
{
	if( !infile.eof() ) {

		  std::string line="";
		  if(getline(infile, line)) {
			  line = replaceAll(line, ":", " : ");
			  line = replaceAll(line, ",", " , ");
			  line = replaceAll(line, "+", " + ");
			  line = replaceAll(line, "-", " - ");
			  line = replaceAll(line, "[", " [ ");
			  line = replaceAll(line, "]", " ] ");
			  line = replaceAll(line, "*", " * ");
			  this->line = new Line(stringSplit(line));
		  }
	}

}

bool Tokenizer::existsCurrentLine()
{
	return !infile.eof() ;
}

bool Tokenizer::isEndOfLine()
{
	return line->isEnd();
}

CheckPoint* Tokenizer::getCurrentCheckPoint()
{
	return new CheckPoint(infile.tellg(),line->getCurrentIndex());
}

void Tokenizer::rollBackToCheckPoint(CheckPoint* point)
{
	this->line->setCurrentIndex(point->getTokenInLineIndex());
	infile.seekg(point->getLinePosition());
}