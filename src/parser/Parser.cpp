#include "Parser.h"
#include "CheckPoint.h"
#include "../statistics/Statistics.h"


Parser::Parser(std::string fileName)
{
	this->tokenizer = new Tokenizer(fileName);

	initRegisters();
	initRegistersPrefixes();
	initSizeWords();
	initOpcodes();
}

Parser::~Parser(void)
{
	delete this->tokenizer;
}

//
//	init functions
//

void Parser::initRegisters()
{
	std::string registersTable[] = {
		"eax", "ebx", "ecx", "edx", "esp", "ebp", "esi", "edi",
		"al", "ah", "bh", "bl", "cl", "dl", "ch", "dh",
		"cs", "ds", "es", "fs", "gs", "ss",
		"eplfags", "eip",
		"ax", "cx", "dx", "bx", "sp", "bp", "si", "di",
		"st",
		"mm7", "mm6", "mm5", "mm4", "mm3", "mm2", "mm1", "mm0"
	};

	registers.insert(registersTable, registersTable + sizeof(registersTable) / sizeof(registersTable[0]));
}

void Parser::initRegistersPrefixes()
{
	std::string registersPrefixesTable[] = {
		"st(", "xmm", "ymm"
	};

	registersPrefixes.insert(registersPrefixesTable, registersPrefixesTable + sizeof(registersPrefixesTable) / sizeof(registersPrefixesTable[0]));
}

void Parser::initOpcodes()
{
	std::string opcodesTable[] = {
		"lock", "rep", "repe", "repne", "ht", "hnt"
	};
	opcodes.insert(opcodesTable, opcodesTable + sizeof(opcodesTable) / sizeof(opcodesTable[0]));
}

void Parser::initSizeWords()
{
	std::string sizeWords[] = {
		"dword", "byte", "word", "qword", "fword", "mmword", "tbyte", "xmmword", "ymmword"
	};

	sizes.insert(sizeWords, sizeWords + sizeof(sizeWords) / sizeof(sizeWords[0]));
}

bool Parser::containsRegisterPrefix(std::string token)
{
	std::set<std::string>::iterator it;
	for( it=registersPrefixes.begin(); it!=registersPrefixes.end(); ++it )
		if(token.find(*it) != std::string::npos)
			return true;

	return false;
}


Statistics* Parser::parse()
{
	std::cout<< "Started parsing ..."  << std::endl;

	//results
	std::vector<Instruction*> instructions;

	while(tokenizer->existsCurrentLine())
	{
		Row* row = line();
		if(row == NULL)
		{
			tokenizer->goToNextLine();
			continue;
		}
		else if( row->getType() == Row::FIRST_ROW)
		{
			Instruction* instruction = new Instruction((FirstRow*) row);
			instructions.push_back(instruction);
			tokenizer->goToNextLine();
		}
		else if( row->getType() == Row::NEXT_ROW )
		{
			instructions.at(instructions.size()-1)->addNextRow((NextRow* ) row);
			tokenizer->goToNextLine();
		}
	}

	return buildStats(instructions);
}

Statistics* Parser::buildStats(std::vector<Instruction*> instructions)
{
	Statistics* stats = new Statistics();

	for( int i = 0 ; i < instructions.size(); ++i)
	{
		Instruction* instr = instructions.at(i);
		if( instr->firstRow->getOpcode().compare("") )
			stats->addOpcode( instr->firstRow->getOpcode());

		if(instr->firstRow->getAssembly() != NULL)
		{
			std::vector<Register*> registers = instr->firstRow->getAssembly()->getRegisters();
			std::vector<Const*> consts = instr->firstRow->getAssembly()->getConsts();

			if( !registers.empty() )
			{
				for( int j =0; j<registers.size(); ++j)
					stats->addRegister( registers.at(j)->getName());
			}

			if( !consts.empty() )
			{
				for( int j =0; j<consts.size(); ++j)
					stats->addConstantLength( consts.at(j)->getConst().length());
			}
		}

		stats->addInstructionLength( instr->getHexes().size());

	}

	return stats;
}

Row* Parser::line()
{
	std::string firstToken = tokenizer->getCurrentToken();

	if(firstToken.length() == 8)
		return firstRow();
	else if(firstToken.length() == 2)
		return nextRow();
	else
		return NULL;
}

FirstRow* Parser::firstRow()
{
	FirstRow* firstRow = new FirstRow();
	address(firstRow);

	if(tokenizer->getCurrentToken() == ":" )
	{
		tokenizer->advance(); // sign :
		
		std::vector<HexSign*> hexSignList = hex();
		firstRow->setHexes(hexSignList);

		//empty opcode...
		if(tokenizer->isEndOfLine())
			return firstRow;

		std::string opCode = opcode();
		firstRow->setOpcode(opCode);

		if( !tokenizer->isEndOfLine() )
		{
			assembly(firstRow);
		}

		return firstRow;
	}
	else
		std::cerr<< "Unexpected symbol: " << tokenizer->getCurrentToken() << " Expected \':\'" <<std::endl;

	return NULL;
}

NextRow* Parser::nextRow()
{
	NextRow* nextRow = new NextRow();
	std::vector<HexSign*> hexSignList = hex();
	nextRow->setHexes(hexSignList);

	if( tokenizer->isEndOfLine() )
		return nextRow;
	else
	{
		std::cerr<< "Unexpected symbol: " << tokenizer->getCurrentToken() << " Expected EOF" <<std::endl;
		delete nextRow;
	}

	return NULL;
}

bool Parser::address(FirstRow* firstRow)
{
	std::string potencialAddress = tokenizer->getCurrentToken();

	if( potencialAddress.length() != 8 )
		return false;

	for( int i=0; i<potencialAddress.length() ; ++i)
	{
		if(!isSign16(potencialAddress[i]))
			return false;
	}

	tokenizer->advance();

	if(firstRow != NULL)
		firstRow->setAddress(potencialAddress);

	return true;
}

std::vector<HexSign*> Parser::hex()
{
	std::vector<HexSign*> hexes;
	while (true)
	{
		std::string oneHexSign = hexSign();
		if(oneHexSign.compare("") != 0 )
		{
			HexSign* newHex = new HexSign();
			newHex->setHex(oneHexSign);
			hexes.push_back(newHex);
		}
		else
			break;
	}

	return hexes;
}

std::string Parser::hexSign()
{
	std::string hex = "";

	if(tokenizer->isEndOfLine())
		return "";
	else
	{
		hex = tokenizer->getCurrentToken();
		if(hex.length() == 2)
		{
			for( int i=0; i<hex.size(); ++i)
			{
				if( !isSign16(hex[i]) )
					return "";
			}

			tokenizer->advance();
			return hex;
		}
		else
			return "";
	}
	return hex; 
}

bool Parser::isSign16(char c)
{
	if( !(isdigit(c) || ( c>= 'A' && c <= 'Z')) )
		return false;
	else
		return true;
}


std::string Parser::opcode()
{
	std::string current = tokenizer->getCurrentToken();
	std::string resultOpcode = current ;

	tokenizer->advance();

	if(!current.compare(""))
	{
		std::cerr << "No signs for opcode! " <<std::endl;
		return "";
	}

	while(isOpcodePrefix(current))
	{
		current = tokenizer->getCurrentToken();
		resultOpcode.append(" ");
		resultOpcode.append(current);
		tokenizer->advance();
	}

	return resultOpcode;
}

bool Parser::isOpcodePrefix(std::string opcode)
{
	if( opcodes.find(opcode) != opcodes.end() )
		return true;
	else
		return false;
}

bool Parser::assembly(FirstRow* firstRow)
{
	AssemblyInstr* instr = new AssemblyInstr();

	while(true)
	{
		AssemblyInstr copyOfRow = *instr;


		//brzydki kawalek, ale wyszedl z zalozen parsera...
		if( !sizeDirective(instr) )
		{
			AssemblyInstr* oldPtr = instr;
			instr = new AssemblyInstr(copyOfRow);
			delete oldPtr;

			if  (!address(NULL) )
			{
				AssemblyInstr* oldPtr = instr;
				instr = new AssemblyInstr(copyOfRow);
				delete oldPtr;

				if( !aloneRegistry(instr) )
				{
					AssemblyInstr* oldPtr = instr;
					instr = new AssemblyInstr(copyOfRow);
					delete oldPtr;

					if(!offset(instr) )
					{
						AssemblyInstr* oldPtr = instr;
						instr = new AssemblyInstr(copyOfRow);
						delete oldPtr;

						if( !jmpArg(instr) )
						{
							AssemblyInstr* oldPtr = instr;
							instr = new AssemblyInstr(copyOfRow);
							delete oldPtr;
							std::cerr<<" Unknown construction in assembly arguments." <<std::endl;
							break;
						}
					}
				}
			}
		}

		std::string current = tokenizer->getCurrentToken();
		if( !tokenizer->getCurrentToken().compare(",") )
			tokenizer->advance();
		else if( tokenizer->isEndOfLine() )
		{
			firstRow->addAssembly(instr);
			return true;
		}

	}

	return false;
}

bool Parser::registry(AssemblyInstr* assembly)
{
	std::string currentToken = tokenizer->getCurrentToken();

	if( (registers.find(currentToken) != registers.end() ) || containsRegisterPrefix(currentToken) )
	{
		if(!currentToken.compare("st("))
		{
			tokenizer->advance(); //eat st(
			currentToken.append(tokenizer->getCurrentToken());
			tokenizer->advance(); //eat -
			currentToken.append(tokenizer->getCurrentToken());
		}
		Register* rej = new Register(currentToken);
		assembly->addRegister( rej );
		tokenizer->advance();
		return true;
	}
	else
		return false;
}

bool Parser::firstRegistry(AssemblyInstr* assembly)
{
	CheckPoint* checkPoint = tokenizer->getCurrentCheckPoint();

	if(!registry(assembly))
		return false;
	else
	{
		if( !tokenizer->getCurrentToken().compare("*"))
		{
			tokenizer->advance();
			if(constant(assembly))
				return true;
			else
			{
				tokenizer->rollBackToCheckPoint(checkPoint);
				delete checkPoint;
				return false;
			}
		}
		else
			return true;
	}
}


bool Parser::constant(AssemblyInstr* assembly)
{
	std::string currentToken = tokenizer->getCurrentToken();

	for(int i=0; i <currentToken.length() ; ++i)
	{
		if( !isalpha(currentToken[i]) && !isSign16(currentToken[i]) )
			return false;
	}

	Const* con = new Const(currentToken);
	assembly->addConst( con );
	tokenizer->advance();
	return true;
}

bool Parser::sizeDirective(AssemblyInstr* assembly)
{
	std::string currentToken = tokenizer->getCurrentToken();

	if(sizes.find(currentToken) == sizes.end() )
		return false;

	CheckPoint* checkPoint = tokenizer->getCurrentCheckPoint();
	
	tokenizer->advance();
	currentToken = tokenizer->getCurrentToken();
	if( !currentToken.compare("ptr"))
		tokenizer->advance();
	else
	{
		tokenizer->rollBackToCheckPoint(checkPoint);
		return false;
	}

	if( !offset(assembly) )
	{
		tokenizer->rollBackToCheckPoint(checkPoint);
		return false;
	}
	else
		return true;
}

bool Parser::offset(AssemblyInstr* assembly)
{
	CheckPoint* checkPoint = tokenizer->getCurrentCheckPoint();

	//opcjonalny rejestr przed offsetem
	if( registry(assembly) )
	{
		if( !tokenizer->getCurrentToken().compare(":"))
			tokenizer->advance();
		else
		{
			tokenizer->rollBackToCheckPoint(checkPoint);
			delete checkPoint;
			return false;
		}
	}

	if( !tokenizer->getCurrentToken().compare("["))
	{
		tokenizer->advance();

		if( !firstRegistry(assembly) && !constant(assembly))
		{
			tokenizer->rollBackToCheckPoint(checkPoint);
			delete checkPoint;
			return false;
		}
		else
		{
			offsetRegister(assembly);
			offsetConst(assembly);

			if( !tokenizer->getCurrentToken().compare("]"))
			{
				tokenizer->advance();
				return true;
			}
			else
			{
				tokenizer->rollBackToCheckPoint(checkPoint);
				delete checkPoint;
				return false;
			}
		}
	}
	else
		return false;
}

bool Parser::offsetRegister(AssemblyInstr* assembly)
{
	std::string currToken = tokenizer->getCurrentToken();
	if(!currToken.compare("+") || !currToken.compare("-") )
	{
		CheckPoint* checkPoint = tokenizer->getCurrentCheckPoint();
		tokenizer->advance();

		if(!firstRegistry(assembly))
		{
			tokenizer->rollBackToCheckPoint(checkPoint);
			delete checkPoint;
			return false;
		}
		else
			return true;
	}
	else
		return false;
}

bool Parser::offsetConst(AssemblyInstr* assembly)
{
	std::string currToken = tokenizer->getCurrentToken();
	if(!currToken.compare("+") || !currToken.compare("-") )
	{
		CheckPoint* checkPoint = tokenizer->getCurrentCheckPoint();
		tokenizer->advance();

		if(!constant(assembly))
		{
			tokenizer->rollBackToCheckPoint(checkPoint);
			delete checkPoint;
			return false;
		}
		else
			return true;
	}
	else
		return false;
}

bool Parser::jmpArg(AssemblyInstr* assembly)
{
	if(!constant(assembly))
		return false;
	else
	{
		if(!tokenizer->getCurrentToken().compare(":"))
		{
			CheckPoint* checkPoint = tokenizer->getCurrentCheckPoint();
			tokenizer->advance();
			if(constant(assembly))
			{
				delete checkPoint;
				return true;
			}
			else
			{
				tokenizer->rollBackToCheckPoint(checkPoint);
				return false;
			}
		}
		else
			return true;
	}
}

bool Parser::aloneRegistry(AssemblyInstr* assembly)
{
	CheckPoint* checkPoint = tokenizer->getCurrentCheckPoint();
	if(!registry(assembly))
	{
		delete checkPoint;
		return false;
	}

	std::string nextToken = tokenizer->getCurrentToken();
	if( nextToken.compare(",") && !tokenizer->isEndOfLine() )
	{
		tokenizer->rollBackToCheckPoint(checkPoint);
		delete checkPoint;
		return false;
	}
	else
		return true;
}