
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main()
{
	std::ifstream myfile;
	std::string string;
	myfile.open("list.txt");
	
	int horizontal_start = INT_MAX;
	int horizontal_end = INT_MIN;
	std::vector<int> Crabs;
	char comma = ',';

	if (myfile.is_open())
	{
		while (myfile.good())
		{
			myfile >> string;
			std::cout << string << "\n";
			std::string horizontal_position;
			while (string.size() > 0 && string != "->")
			{
				auto itr = string.begin();
				char number = *itr;
				horizontal_position.push_back(number);
				if (*itr == comma)
				{
					int num = std::stoi(horizontal_position);
					//std::cout << "coordinate_string " << num << "\n";
					horizontal_start = std::min(num, horizontal_start);
					horizontal_end = std::max(num, horizontal_end);
					Crabs.push_back(num);

					horizontal_position.clear();
				}
				string.erase(itr);
				if (string.size() == 0)
				{
					int num = std::stoi(horizontal_position);
					//std::cout << "coordinate_string " << num << "\n";
					horizontal_start = std::min(num, horizontal_start);
					horizontal_end = std::max(num, horizontal_end);
					Crabs.push_back(num);

					horizontal_position.clear();
				}
			}
		}
	}


	std::pair<int, int> paired_fuel_cost;
	paired_fuel_cost = std::pair<int, int>(0, INT_MAX);
	for (int horizontal_position = horizontal_start; horizontal_position <= horizontal_end; horizontal_position++)
	{
		int fuel_cost = 0;
		for (auto crab : Crabs)
		{
			int crab_cost = 0;
			int crab_fuel_cost = -1;
	
			for (int i = crab; i <= horizontal_position; i++)
			{
				crab_fuel_cost++;
				crab_cost += crab_fuel_cost;
				//std::cout << "crab_fuel_cost " << crab_fuel_cost << " crab_cost " << crab_cost << "\n";
			}
			
			for (int i = crab; i >= horizontal_position; i--)
			{
				crab_fuel_cost++;
				crab_cost += crab_fuel_cost;
			//	std::cout << "crab_fuel_cost " << crab_fuel_cost << " crab_cost " << crab_cost << "\n";
			}
			fuel_cost += crab_cost;
					
//			std::cout << "Move from " << crab << " to " << horizontal_position << ": " << crab_fuel_cost << " fuel" << "\n";
		}

		if (fuel_cost < paired_fuel_cost.second)
		{
			paired_fuel_cost.first = horizontal_position;
			paired_fuel_cost.second = fuel_cost;
		}

		std::cout << "horizontal_position " << horizontal_position << " fuel_cost " << fuel_cost << "\n";
	}
	std::cout << "lowest position " << paired_fuel_cost.first << " cost " << paired_fuel_cost.second;

}