

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <algorithm>
#include <iomanip>



int main()
{
	std::ifstream myfile;
	myfile.open("list.txt");
	std::string mystring;
	int count = 0;
	int horizontal_position = 0;
	int depth = 0;
	int aim = 0;
	std::string input;

	if (myfile.is_open()) {
		while (myfile.good())
		{
			myfile >> mystring;
			//	std::cout << mystring << "\n";

			if (mystring == "forward" || mystring == "up" || mystring == "down")
			{
				input = mystring;
				continue;
			}

			if (input == "forward")
			{
				int X = std::stoi(mystring);
				horizontal_position += X;
				
				std::cout << "forward " << X << " horizontal position " << horizontal_position << "\n";
				
				if (aim != 0)
				{
					depth += aim * X;
					std::cout  << "aim " << aim << " num " << X << " Depth " << depth << "\n";
				}
			}
			if (input == "up")
			{
				int X = std::stoi(mystring);
				//depth -= X;
				aim -= X;
				std::cout << "up " << X << " depth " << depth << " aim " << aim << "\n";			
			}
			if (input == "down")
			{
				int X = std::stoi(mystring);
				//depth += X;
				aim += X;
				std::cout << "down " << X << " depth " << depth << " aim " << aim	 << "\n";
			}
		}
	}
	std::cout << "final depth " << depth << "\n";
	std::cout << "final horizontal position " << horizontal_position << "\n";
	count = horizontal_position * depth;
	std::cout << "count " << count;
}
