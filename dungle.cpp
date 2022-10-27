//TODO: Refactor this in C, lol


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

uint8_t parseData(std::string line, uint8_t MSB)
{
	line.erase(0,6);
	std::string subline;

	uint8_t dungleline = MSB;
	uint8_t mask	   = 0x80;

	for(int i = 1; i < 8; i++)
	{
		subline = line.substr(0,6);
		if(subline == "Dingle")	dungleline = dungleline | (mask>>i);
		line.erase(0,6);
	}

	return dungleline;
}

void execDungCmd(uint8_t cmd, uint8_t *regs)
{
	uint8_t    op = cmd & 0xF0;
	uint8_t param = cmd & 0x0F;

	switch(op)
	{
		case 0x80:	// add value in active reg to mem addr [param]
			regs[param] = regs[param] + regs[0x0F];
			break;
		case 0x90:	// add immediate value to active reg
			regs[0x0F] = regs[0x0F] + param;
			break;
		case 0xA0:	// left shit value at addr [param]
			regs[param] = regs[param]<<1;
			break;
		case 0xB0:	// right shift value ar add [param]
			regs[param] = regs[param]>>1;
			break;
		case 0xC0:	// XOR value at addr [param] with value in active reg
			regs[param] = regs[param] ^ regs[0x0F];
			break;
		case 0xD0:	// OR value at addr [param] with value in active reg
			regs[param] = regs[param] | regs[0x0F];
			break;
		case 0xE0:	// AND value at addr [param] with value in active reg
			regs[param] = regs[param] & regs[0x0F];
			break;
		case 0xF0:	// print value at addr [param]
			std::cout << regs[param] << std::endl;
			break;
		default:
			std::cout << "Invalid Command: " << std::hex << unsigned(cmd) << std::endl;
	}
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		std::cout << "Expected an input file\n";
		return 1;
	}


	std::string filename(argv[1]);

	std::string line;

	uint8_t *DungData = new uint8_t[0x10];	//want addresses 0x00-0x0F
	for(uint8_t i = 0; i < 0x10; i++)	
		DungData[i] = 0;		//initialize our 15 registers

	std::ifstream file;
	file.open(filename);

	if(file.is_open())
	{
		while(file)
		{
			std::getline(file, line);
			if(line.find("Dongle") != std::string::npos ||
				line.find("Dingle") != std::string::npos)
				if(line.substr(0,6) == "Dongle") 		//store data in "active"
				{
					DungData[0x0F] = parseData(line, 0x00);
					//std::cout << std::hex << short(DungData[0x0F]) << std::endl;
				}
				else if(line.substr(0,6) == "Dingle")		//execute dungle command
				{
					execDungCmd(parseData(line, 0x80), DungData);
				}
			else continue;
		}	
		file.close();
	}
	std::cout << std::endl;
	return 0;
}
