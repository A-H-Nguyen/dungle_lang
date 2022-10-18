//TODO: Refactor this in C, lol


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

char parseData(std::string line)
{
	line.erase(0,6);
	std::string subline;

	short dungleline = 0x0000;
	short mask	 = 0x0080;

	for(int i = 1; i < 8; i++)
	{
		subline = line.substr(0,6);
		std::cout << subline << std::endl;
		if(subline == "Dingle")
		{
			dungleline = dungleline | (mask>>i);
		}
		line.erase(0,6);
	}
	return char(dungleline);
}
/*
void execDungCmd(char cmd)
{
	char op = cmd & 0xF0;
	switch(op)
	{
		case 0x80:	//
		case 0x90:
		case 0xA0:
		case 0xB0:
		case 0xC0:
		case 0xD0:
		case 0xE0:
		case 0xF0:
	}
}
*/
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Expected an input file\n";
		return 1;
	}


	std::string filename(argv[1]);

	std::string line;
	char active;
	char command;

	char *DungData = new char[0x7F];

	std::ifstream file;
	file.open(filename);

	if(file.is_open())
	{
		while(file)
		{
			std::getline(file, line);
			if(line.find("DUNG: ") != std::string::npos) 		//store data in "active"
			{
				std::cout << line << std::endl;
				active = parseData(line);
				std::cout << std::hex << uint16_t(active) << std::endl;
			}
			else if(line.find("D!NG: ") != std::string::npos)	//execute dungle command
			{
				//command = parseData(line);
				//execDungCmd(command);
				std::cout << "hoi\n";
			}
			else continue;
		}	
		file.close();
	}

	//for(int i = 0; i < dungChars.size(); i++) printf("%c", dungChars.at(i));
	//std::cout << std::endl;
	//for(int i = 0; i < dungInts.size(); i++) printf("%d", dungInts.at(i)); 
	//std::cout << std::endl;

	return 0;
}
