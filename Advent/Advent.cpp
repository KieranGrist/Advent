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
	if (myfile.is_open()) {
		while (myfile.good())
		{
			myfile >> mystring;
			int num = std::stoi(mystring);
			int current_sum = num;

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

		}
	}

	std::cout << "count " << count;
}
