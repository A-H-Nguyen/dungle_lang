#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void parseDungleLine(std::string line)
{
	std::string subline;

	uint16_t dungleline = 0x0000;
	uint16_t mask 	    = 0x0080;

	if(subline.find(" ") != std::string::npos)
	{
		std::cout << std::endl;
	}
	else
	{
		for(int i = 0; i < 8; i++)
		{
			subline = line.substr(0,6);
			//std::cout << subline << std::endl;
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
		//std::cout << std::hex << dungleline << ", " << char(dungleline);
		std::cout << char(dungleline);
	}
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Expected an input file\n";
		return 1;
	}

	std::vector<std::string> inputCode;
	//std::vector<uint16_t> dungleCode;

	std::string filename(argv[1]);
	std::string line;

	std::ifstream file;
	file.open(filename);

	if(file.is_open())
	{
		while(file)
		{
			std::getline(file, line);
			inputCode.push_back(line);
		}	
		file.close();
	}

	for(int i = 0; i < inputCode.size(); i++)
	{
		//std::cout << inputCode.at(i) << " | ";
		parseDungleLine(inputCode.at(i));
		//std::cout << std::endl;
	}
	std::cout << std::endl;
	return 0;
}
