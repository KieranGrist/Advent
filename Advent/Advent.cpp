
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

struct Fishes
{
	Fishes()
	{

	}

	Fishes(const Fishes& fish)
	{
		Zero = fish.Zero;
		One = fish.One;
		Two = fish.Two;
		Three = fish.Three;
		Four = fish.Four;
		Five = fish.Five;
		Six = fish.Six;
		Seven = fish.Seven;
		Eight = fish.Eight;
	}

	int64_t Count()
	{
		return Zero + One + Two + Three + Four + Five + Six + Seven + Eight;
	}

	void Print()
	{
		std::cout << Zero << " " << One << " " << Two << " " << Three << " " << Four << " " << Five << " " << Six << " " << Seven << " " << Eight << "\n";
	}

	void AddFish(int InNum)
	{
		switch (InNum)
		{
		case 0:
			Zero++;
			break;
		case 1:
			One++;
			break;
		case 2:
			Two++;
			break;
		case 3:
			Three++;
			break;
		case 4:
			Four++;
			break;
		case 5:
			Five++;
			break;
		case 6:
			Six++;
		case 7:
			Seven++;
			break;;
		case 8:
			Eight++;
			break;
		}
	}

	void PassDay()
	{
		Fishes fish(*this);
		Zero = fish.One;
		One = fish.Two;
		Two = fish.Three;
		Three = fish.Four;
		Four = fish.Five;
		Five = fish.Six;
		Six = fish.Seven + fish.Zero;
		Seven = fish.Eight;
		Eight = 0 + fish.Zero;
	}

	int64_t Zero = 0;
	int64_t One = 0;
	int64_t Two = 0;
	int64_t Three = 0;
	int64_t Four = 0;
	int64_t Five = 0;
	int64_t Six = 0;
	int64_t Seven = 0;
	int64_t Eight = 0;
};

int64_t FishCount(std::vector<int> FishTracker)
{
	int count = 0;
	for (auto fish : FishTracker)
	{
		count += fish;
	}
	return count;
}
int main()
{
	std::ifstream myfile;
	std::string string;
	myfile.open("list.txt");

	Fishes fishes;
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
					fishes.AddFish(num);

					fish_string.clear();
				}
				string.erase(itr);
				if (string.size() == 0)
				{
					int num = std::stoi(fish_string);
					//std::cout << "coordinate_string " << num << "\n";
					fishes.AddFish(num);
					fish_string.clear();
				}
			}

		}
	}

	for (int64_t day = 0; day <= 256; day++)
	{
		std::cout << "Day " << day << ":";
		if (day == 0)
		{
			std::cout << "Fishes " << fishes.Count() << "\n";
			fishes.Print();
			continue;
		}	
		fishes.PassDay();
		std::cout << "Fishes " << fishes.Count() << "\n";
		fishes.Print();		
	}
	std::cout << "Fishes " << fishes.Count() << "\n";
	std::cin.ignore();
}