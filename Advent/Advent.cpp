

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <algorithm>
#include <iomanip>
using namespace::std;


int main()
{
	std::ifstream myfile;
	myfile.open("list.txt");
	std::string mystring;
	int count = 0;
	int previous_sum_amount = -1;
	vector<int> numbers;
	if (myfile.is_open()) {
		while (myfile.good())
		{
			myfile >> mystring;
			int num = std::stoi(mystring);
			numbers.push_back(num);
		}
	}

	int alpha_index = 0;
	int bravo_index = 1;
	int charlie_index = 2;
	
	for (int i = 0; i < numbers.size(); i++)
	{
		alpha_index = i;
		bravo_index = alpha_index + 1;
		if (numbers.size() <= bravo_index)
			break;
		charlie_index = bravo_index + 1;
		if (numbers.size() <= charlie_index)
			break;

		int alpha_num = numbers[alpha_index];
		int bravo_num = numbers[bravo_index];
		int charlie_num = numbers[charlie_index];

		int current_sum = alpha_num + bravo_num + charlie_num;

		if (previous_sum_amount == -1)
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
