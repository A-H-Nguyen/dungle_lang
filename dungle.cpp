#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

char parseChar(std::string line)
{
	line.erase(0,1);
	std::string subline;

	uint16_t dungleline = 0x0000;
	uint16_t mask 	    = 0x0080;

	for(int i = 0; i < 8; i++)
	{
		subline = line.substr(0,6);
		if(subline == "Dongle")
		{
			dungleline = dungleline | (mask>>i);
		}
		else if(subline == "Dingle")
		{
			dungleline = dungleline | 0x0000;
		}
		else
		{
			break;
		}
		line.erase(0,6);
	}
	return char(dungleline);
}

short parseInt(std::string line)
{
	line.erase(0,1);
	std::string subline;

	uint16_t dungleline = 0x0000;
	uint16_t mask 	    = 0x0080;

	for(int i = 0; i < 8; i++)
	{
		subline = line.substr(0,6);
		if(subline == "Dongle")
		{
			dungleline = dungleline | (mask>>i);
		}
		else if(subline == "Dingle")
		{
			dungleline = dungleline | 0x0000;
		}
		else
		{
			break;
		}
		line.erase(0,6);
	}
	return short(dungleline);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Expected an input file\n";
		return 1;
	}

	std::vector<std::string> inputCode;
	std::vector<char> dungChars;
	std::vector<short> dungInts;

	std::string filename(argv[1]);
	std::string line;

	std::string newdung;

	std::ifstream file;
	file.open(filename);

	if(file.is_open())
	{
		while(file)
		{
			std::getline(file, line);
			inputCode.push_back(line);

			if(line.find("!") != std::string::npos)
			{
				dungChars.push_back(parseChar(line));
			}

			if(line.find("#") != std::string::npos)
			{
				dungInts.push_back(parseInt(line));
			}
		}	
		file.close();
	}

	for(int i = 0; i < dungChars.size(); i++) printf("%c", dungChars.at(i));
	std::cout << std::endl;
	for(int i = 0; i < dungInts.size(); i++) printf("%d", dungInts.at(i)); 
	std::cout << std::endl;

	return 0;
}
