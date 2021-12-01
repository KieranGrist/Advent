

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <algorithm>
#include <iomanip>
using namespace::std;

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

	int AddUp()
	{
		return FirstNum + SecondNum + ThirdNum;
	}
	
	bool AllNumbers() { return FirstNum != 0 && SecondNum != 0 && ThirdNum != 0; };

	int FirstNum = 0;
	int SecondNum = 0;
	int ThirdNum = 0;
};

char int_to_letter(int n)
{
	//n = std::clamp(n, 1, 26);
	return "abcdefghijklmnopqrstuvwxyz"[n - 1];
}

int main()
{
	std::ifstream myfile;
	myfile.open("list.txt");
	std::string mystring;
	int count = 0;
	int previous_sum_amount = 0;
	vector<int> numbers;
	if (myfile.is_open()) {
		while (myfile.good())
		{
			myfile >> mystring;
			int num = std::stoi(mystring);
			numbers.push_back(num);
		}
	}

	int index = 0;
	int row = 0;
	std::map<int, Sum> sums;

	auto alpha_sum = sums.find(0);
	auto bravo_sum = sums.find(0);
	auto charlie_sum = sums.find(0);
	int alpha_index = 0;
	int bravo_index = 1;
	int charlie_index = 2;
	
	cout << "\tNUM\tLETTER\n";
	for (auto itr = numbers.begin(); itr != numbers.end(); ++itr)
	{
		alpha_index = row;
		bravo_index = alpha_index + 1;
		charlie_index = bravo_index + 1;
		alpha_sum = sums.find(alpha_index);
		bravo_sum = sums.find(bravo_index);
		charlie_sum = sums.find(charlie_index);
		
		index++;
		switch (index)
		{
		case 1:
			cout << '\t' << *itr << '\t' << int_to_letter(alpha_index) << '\n';
		case 2:		
			cout << '\t' << *itr << '\t' << int_to_letter(alpha_index) << '\n';
			cout << '\t' << *itr << '\t' << int_to_letter(bravo_index) << '\n';
		case 3:
			cout << '\t' << *itr << '\t' << int_to_letter(alpha_index) << '\n';
			cout << '\t' << *itr << '\t' << int_to_letter(bravo_index) << '\n';
			cout << '\t' << *itr << '\t' << int_to_letter(charlie_index) << '\n';

			row++;
			index = 0;
			break;		
		}
	}

	for (auto itr = sums.begin(); itr != sums.end(); ++itr)
	{
		int current_sum = itr->second.AddUp();

		if (previous_sum_amount == 0)
		{
			std::cout << current_sum << " (N/A - no previous measurement)" << "\n";
			previous_sum_amount = current_sum;
			continue;
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

	std::cout << "count " << count;
}
