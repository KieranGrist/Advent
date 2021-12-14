
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <algorithm>
#include <iomanip>
struct BinaryNumber
{
public:
	BinaryNumber()
	{
		BinaryString.clear();
		Bits.clear();
	};

	BinaryNumber(const BinaryNumber& InBinaryNumber)
	{
		Bits = InBinaryNumber.Bits;
		BinaryString = InBinaryNumber.BinaryString;
	};
	
	void SetString(std::string InString)
	{
		BinaryString = InString;
		for (std::string::size_type i = 0; i < BinaryString.size(); i++)
		{
			int bin = -1;
			if (BinaryString[i] == '0')
			{
				bin = 0;
			}
			else
			{
				bin = 1;
			}
			AddBit(bin);
		}
	}
	
	int GetRow(int InRow)
	{
		return Bits[InRow];
	}

	void AddBit(int InBit)
	{
		Bits.push_back(InBit);
	}
	
	const std::string& GetString()
	{
		return BinaryString;
	}

private:
	std::string BinaryString;
	std::vector<int> Bits;
};
struct BinaryVector
{
public:
	BinaryVector()
	{
		BinaryNumbers.clear();
	}
	
	BinaryVector(const BinaryVector& InBinaryNumber)
	{
		BinaryNumbers = InBinaryNumber.BinaryNumbers;
	};
	
	std::map<std::string, BinaryNumber>::iterator FindBinaryStorage(std::string InString)
	{
		return BinaryNumbers.find(InString);
	}
	
	BinaryNumber GetFirstBinaryNumber()
	{
		auto number = BinaryNumbers.begin();
		return number->second;
	}
	
	void AddBinaryNumber(BinaryNumber InBinary)
	{
		if (FindBinaryStorage(InBinary.GetString()) != BinaryNumbers.end())
			return;
		BinaryNumbers.emplace(InBinary.GetString(), InBinary);
	}
	
	size_t RemoveBinaryNumber(std::string InString)
	{
		return BinaryNumbers.erase(InString);
	}
	
	int Count()
	{
		return BinaryNumbers.size();
	}

	std::map<std::string, BinaryNumber> BinaryNumbers;
};
int main()
{
	std::cout << "Hello, world!";
	std::ifstream myfile;
	std::string binary_string;
	myfile.open("list.txt");
	int count = 0;
	int size = 0;
	BinaryVector binary_vector;
	std::map<int, BinaryVector> mapped_zeros;
	std::map<int, BinaryVector> mapped_ones;
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			myfile >> binary_string;
			//std::cout << "binary string " << binary_string << "\n";
			size = binary_string.length();
			BinaryNumber number;
			number.SetString(binary_string);
			binary_vector.AddBinaryNumber(number);
			for (int row = 0; row < size; row++)
			{
				//  std::cout << "binary string  " << num.GetString() << "\n";
				int row_num = number.GetRow(row);
				//  std::cout << "row " << row << " num " << row_num << "\n";
				switch (row_num)
				{
				case 0:
					mapped_zeros[row].AddBinaryNumber(number);
					break;
				case 1:
					mapped_ones[row].AddBinaryNumber(number);
					break;
				}
			}
		}
	}
	// Find the Oxygen rating 
	int numbers_left = 0;
	BinaryVector oxygen_vector = binary_vector;
	BinaryVector co2_vector = binary_vector;
	//  std::cout << "oxygen generator start"<< "\n";
	for (int position = 0; position < size; position++)
	{
		BinaryVector zeroes = mapped_zeros[position];
		BinaryVector ones = mapped_ones[position];
		int zero_count = zeroes.Count();
		int one_count = ones.Count();

		if (one_count > zero_count)
		{
			// oxygen_generator_number : Throw out all the numbers with a 0 in the position
			for (auto itr = zeroes.BinaryNumbers.begin(); itr != zeroes.BinaryNumbers.end(); ++itr)
			{
				if (oxygen_vector.Count() == 1)
					break;
				oxygen_vector.RemoveBinaryNumber(itr->first);
			}
			// CO2_scrubber_rating : Throw out all numbers with a 1 in position 
			for (auto itr = ones.BinaryNumbers.begin(); itr != ones.BinaryNumbers.end(); ++itr)
			{
				if (co2_vector.Count() == 1)
					break;
				co2_vector.RemoveBinaryNumber(itr->first);
			}
		}
		if (zero_count > one_count)
		{
			// oxygen_generator_number : Throw out all the numbers with a 1 in the position
			for (auto itr = ones.BinaryNumbers.begin(); itr != ones.BinaryNumbers.end(); ++itr)
			{
				if (oxygen_vector.Count() == 1)
					break;
				oxygen_vector.RemoveBinaryNumber(itr->first);
			}
			// CO2_scrubber_rating : Throw out all numbers with a 0 in position 
			for (auto itr = zeroes.BinaryNumbers.begin(); itr != zeroes.BinaryNumbers.end(); ++itr)
			{
				if (co2_vector.Count() == 1)
					break;
				co2_vector.RemoveBinaryNumber(itr->first);
			}
		}
		if (zero_count == one_count)
		{
			// oxygen_generator_number : Keep all the numbers with a 1 in the position 
			for (auto itr = zeroes.BinaryNumbers.begin(); itr != zeroes.BinaryNumbers.end(); ++itr)
			{
				if (oxygen_vector.Count() == 1)
					break;
				oxygen_vector.RemoveBinaryNumber(itr->first);
			}
			// CO2_scrubber_rating : Throw out all numbers with a 0 in position 
			for (auto itr = ones.BinaryNumbers.begin(); itr != ones.BinaryNumbers.end(); ++itr)
			{
				if (co2_vector.Count() == 1)
					break;
				co2_vector.RemoveBinaryNumber(itr->first);
			}
		}
		if (co2_vector.Count() == 1 && oxygen_vector.Count() == 1)
			break;
	}
	auto oxygen_generator_number = oxygen_vector.GetFirstBinaryNumber();
	auto co2_binary_number = co2_vector.GetFirstBinaryNumber();
	int oxygen_generator_rating = std::stoi(oxygen_generator_number.GetString(), nullptr, 2);
	int CO2_scrubber_rating = std::stoi(co2_binary_number.GetString(), nullptr, 2);
	std::cout << "oxygen_generator_rating " << oxygen_generator_rating << " CO2_scrubber_rating " << CO2_scrubber_rating << "\n";
	count = oxygen_generator_rating * CO2_scrubber_rating;
	std::cout << "count " << count;
}