// Advent.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


struct Sum
{

	std::string ToString()
	{
		return "(First Num:" + std::to_string(FirstNum) + ", Second Num: " + std::to_string(SecondNum) + ", Third Num: " + std::to_string(ThirdNum) + ")";
	}

	void PlaceNumber(int InNum)
	{
		if (FirstNum == 0)
		{
			FirstNum = InNum;
			return;
		}

		if (SecondNum == 0)
		{
			SecondNum = InNum;
			return;
		}

		if (ThirdNum == 0)
		{
			ThirdNum = InNum;
			return;
		}
	}

	int FirstNum = 0;
	int SecondNum = 0;
	int ThirdNum = 0;
};


int main()
{
	std::ifstream myfile;
	myfile.open("list.txt");
	std::string mystring;
	int count = 0;
	int previous_sum_amount = 0;
	int random_thing = 0;
	std::map<int, Sum> sums;
	std::map<int, int> table_thing;

	if (myfile.is_open()) {
		while (myfile.good())
		{
			myfile >> mystring;
			int num = std::stoi(mystring);

		
			if (random_thing == 3)
			{
				random_thing = 0;
			}
			random_thing++;

			switch (random_thing)
			{
			case  1:

				break;
			case 2: 
				break;
			case 3:
				break;
			}


			auto table_itr = table_thing.find(row);
			if (table_itr != table_thing.end())
			{
				table_itr->second++;
			}
			else
			{
				table_thing.insert(std::pair<int, int>(row, 0));
				table_itr = table_thing.find(row);
			}

			auto itr = sums.find(table_itr->second);
			if (itr != sums.end())
			{
				itr->second.PlaceNumber(num);
			}
			else
			{
				Sum sum;
				sum.PlaceNumber(num);
				sums.insert(std::pair<int, Sum>(table_itr->second, sum));
			}


			/*
			current_sum += num;
			numbers_met++;

			if (numbers_met == 2)
			{
				if (previous_sum_amount == 0)
				{
					std::cout << num << " (N/A - no previous measurement)" << "\n";
				}
				if (current_sum > previous_sum_amount)
				{
					std::cout << current_sum << " (increased)" << "\n";
					count++;
				}
				if (current_sum == previous_sum_amount)
				{
					std::cout << current_sum << " (no change)" << "\n";

				}
				if (current_sum < previous_sum_amount)
				{
					std::cout << current_sum << " (decreased)" << "\n";
				}
				previous_sum_amount = current_sum;
				numbers_met = 0;
				current_sum = 0;
			}
			*/
		}
	}


	std::cout << "\tKEY\tELEMENT\n";
	for (auto itr = sums.begin(); itr != sums.end(); ++itr)
	{
		std::cout << '\t' << itr->first << '\t' << itr->second.ToString() << '\n';
	}


	std::cout << "count " << count;
}
