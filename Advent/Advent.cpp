

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
	
	std::map<int, std::vector<int>> mapped_column_numbers;

	if (myfile.is_open()) {
		while (myfile.good())
		{
			myfile >> mystring;
			std::cout << "mystring  " << mystring <<"\n";

			for (std::string::size_type i = 0; i < mystring.size(); i++)
			{
				int bin = -1;
				if (mystring[i] == '0')
				{
					bin = 0;
				}
				else
				{
					bin = 1;
				}
			
				std::cout << "column i " << i << " had binary " <<bin << "\n";
				auto column_pair = mapped_column_numbers.find(i);
				if (column_pair != mapped_column_numbers.end())
				{
					column_pair->second.push_back(bin);
				}
				else
				{
					std::vector<int> array;
					array.push_back(bin);
					mapped_column_numbers.emplace(i, array);
				}
			}
		}
	}
	std::string gamma = "";
	std::string epsilon = "";

	for (auto it = mapped_column_numbers.begin(); it != mapped_column_numbers.end(); it++)
	{
		int zero = 0;
		int one = 0;
		std::vector<int> num_array = it->second;
		for (int num : num_array)
		{
			switch (num)
			{
			case 0:
				zero++;
				break;
			case 1:
				one++;
				break;			
			}
		}

		std::cout << "column  " << it->first << " zeros: " << zero << " ones: " << one << "\n";

		if (zero > one)
		{
			gamma.append("0");
			epsilon.append("1");
		}
		else
		{
			gamma.append("1");
			epsilon.append("0");
		}
		std::cout << "gamma " << gamma << "\n";
		std::cout << "epsilon " << epsilon << "\n";


	}
	int gamma_rate = std::stoi(gamma, nullptr, 2);
	int epsilon_rate = std::stoi(epsilon, nullptr, 2);

	std::cout << "gamma_rate " << gamma_rate << "\n";
	std::cout << "epsilon_rate " << epsilon_rate << "\n";

	count = gamma_rate * epsilon_rate;

	std::cout << "count " << count;
}
