
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

struct Fish
{
	Fish(int InStarTime = 9)
	{
		InternalTimer = InStarTime;
	}

	int InternalTimer = -1;

};

int main()
{
	std::ifstream myfile;
	std::string string;
	myfile.open("list.txt");
	std::vector<Fish> Fishies;
	char comma = ',';

	if (myfile.is_open())
	{
		while (myfile.good())
		{
			myfile >> string;
			std::cout << string << "\n";
			std::string fish_string;
		
			while (string.size() > 0 && string != "->")
			{
				auto itr = string.begin();
				char number = *itr;
				fish_string.push_back(number);
				if (*itr == comma)
				{
					int num = std::stoi(fish_string);
					//std::cout << "coordinate_string " << num << "\n";
					Fishies.push_back(Fish(num));
					fish_string.clear();
				}
				string.erase(itr);
				if (string.size() == 0)
				{
					int num = std::stoi(fish_string);
					//std::cout << "coordinate_string " << num << "\n";
					Fishies.push_back(Fish(num));
					fish_string.clear();
				}
			}

		}
	}
	int fishes_to_create = 0;

	for (int day = 0; day <= 80; day++)
	{
		if (day == 0)
		{
			std::cout << "Initial state: ";
		}
		else
		{
			std::cout << "After: " << day <<" " << std::string(day > 1 ? "days" : " day") << ": ";
		}

		for (int i = 0; i < fishes_to_create; i++)
		{
			Fishies.push_back(Fish());
		}

		fishes_to_create = 0;

		for (auto fish = Fishies.begin(); fish != Fishies.end(); ++fish)
		{
			if (day == 0)
			{
				//std::cout << fish->InternalTimer << ",";
				continue;
			}

			fish->InternalTimer--;
			//std::cout << fish->InternalTimer << ",";
			
			if (fish->InternalTimer == 0)
			{
				fishes_to_create++;
				fish->InternalTimer = 7;
			}		
		}
		
		//std::cout << "\n";

		std::cout << "Fishes " << Fishies.size();
		
		std::cout << "\n";
	}
	std::cout << "Fishes " << Fishies.size();
	std::cin.ignore();
}