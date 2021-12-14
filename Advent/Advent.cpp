
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

	void RemoveRow(int InRow)
	{
		Bits.erase(Bits.begin() + InRow);
	}
	
	void Print()
	{
		for (auto itr : Bits)
		{
			std::cout << itr;
		}
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
	
	size_t Count()
	{
		return BinaryNumbers.size();
	}

	size_t RemoveBinaryNumber(std::string InString)
	{
		return BinaryNumbers.erase(InString);
	}
	
	std::map<std::string, BinaryNumber> BinaryNumbers;
};


struct OxgenVector : public BinaryVector
{
public: 
	OxgenVector(const BinaryVector& InBinaryNumber)
	{
		BinaryNumbers = InBinaryNumber.BinaryNumbers;
	};

	void Print(int Position)
	{
		std::cout << "Oxygen Vector Numbers Readout Position " << Position  << "\n";
		for (auto itr = BinaryNumbers.begin(); itr != BinaryNumbers.end(); ++itr)
		{
			itr->second.Print();
			std::cout << "\n";
		}
	}

	std::string FindOxygenRating()
	{
		/*
		 To find oxygen generator rating,
		 determine the most common value (0 or 1) in the current bit position,
		 and keep only numbers with that bit in that position. 
		 if 0 and 1 are equally common, keep values with a 1 in the position being considered.
		*/
		size_t size = BinaryNumbers.size();
		int pos = 0;
		while (size != 1)
		{
			Print(pos);
		
			std::vector<std::string> zeros;
			std::vector<std::string> ones;
			for (auto itr = BinaryNumbers.begin(); itr != BinaryNumbers.end(); ++itr)
			{
				int row_num = itr->second.GetRow(0);
				itr->second.RemoveRow(0);
				switch (row_num)
				{
				case 0:
					zeros.push_back(itr->first);
					break;
				case 1:
					ones.push_back(itr->first);
					break;
				}
			}

			int zero_count = zeros.size();
			int one_count = ones.size();
			std::cout << "zero_count " << zero_count << " one_count " << one_count << " Count " << Count() << "\n";
			if (zero_count > one_count)
			{
				for (auto itr : ones)
				{
					RemoveBinaryNumber(itr);
					size = Count();
					if (size == 1)
						break;
				}
			}
			
			if (one_count > zero_count)
			{
				for (auto itr : zeros)
				{
					RemoveBinaryNumber(itr);
					size = Count();
					if (size == 1)
						break;
				}
			}

			if (one_count == zero_count)
			{
				
				for (auto itr : zeros)
				{
					RemoveBinaryNumber(itr);
					size = Count();
					if (size == 1)
						break;
				}
			}
			pos++;
		}

		auto OxygenRating = BinaryNumbers.begin()->first;
		std::cout << "OxygenRating " << OxygenRating << "\n";
		return OxygenRating;
	}
};

struct CO2Vector : public BinaryVector
{
public:
	CO2Vector(const BinaryVector& InBinaryNumber)
	{
		BinaryNumbers = InBinaryNumber.BinaryNumbers;
	};

	void Print(int Position)
	{
		std::cout << "CO2 Vector Numbers Readout Position " << Position << "\n";
		for (auto itr = BinaryNumbers.begin(); itr != BinaryNumbers.end(); ++itr)
		{
			itr->second.Print();
			std::cout << "\n";
		}
	}

	std::string FindC02ScruberRating()
	{
		/*
		* To find CO2 scrubber rating, 
		determine the least common value (0 or 1) in the current bit position,
		and keep only numbers with that bit in that position.
		If 0 and 1 are equally common, keep values with a 0 in the position being considered.
		*/

		size_t size = BinaryNumbers.size();
		int pos = 0;
		while (size != 1)
		{
			Print(pos);
			pos++;
			std::vector<std::string> zeros;
			std::vector<std::string> ones;
			for (auto itr = BinaryNumbers.begin(); itr != BinaryNumbers.end(); ++itr)
			{
				int row_num = itr->second.GetRow(0);
				itr->second.RemoveRow(0);
				switch (row_num)
				{
				case 0:
					zeros.push_back(itr->first);
					break;
				case 1:
					ones.push_back(itr->first);
					break;
				}
			}

			int zero_count = zeros.size();
			int one_count = ones.size();
			std::cout << "zero_count " << zero_count << " one_count " << one_count << " Count " << Count() << "\n";

			if (zero_count < one_count)
			{
				for (auto itr : ones)
				{
					RemoveBinaryNumber(itr);
					size = Count();
					if (size == 1)
						break;
				}
			}

			if (one_count < zero_count)
			{
				for (auto itr : zeros)
				{
					RemoveBinaryNumber(itr);
					size = Count();
					if (size == 1)
						break;
				}
			}

			if (one_count == zero_count)
			{
				for (auto itr : ones)
				{
					RemoveBinaryNumber(itr);
					size = Count();
					if (size == 1)
						break;
				}
			}
			size = Count();
		}
		auto C02ScruberRating = BinaryNumbers.begin()->first;
		std::cout << "C02ScruberRating " << C02ScruberRating << "\n";
		return C02ScruberRating;
	}
};
int main()
{
	std::ifstream myfile;
	std::string binary_string;
	myfile.open("list.txt");
	int count = 0;
	int size = 0;
	BinaryVector binary_vector;
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
		}
	}
	// Find the Oxygen rating 
	int numbers_left = 0;
	OxgenVector oxygen_vector = binary_vector;
	CO2Vector co2_vector = binary_vector;

	auto oxygen_generator_number = oxygen_vector.FindOxygenRating();
	auto co2_binary_number = co2_vector.FindC02ScruberRating();
	int oxygen_generator_rating = std::stoi(oxygen_generator_number, nullptr, 2);
	int CO2_scrubber_rating = std::stoi(co2_binary_number, nullptr, 2);
	std::cout << "oxygen_generator_rating " << oxygen_generator_rating << " CO2_scrubber_rating " << CO2_scrubber_rating << "\n";
	count = oxygen_generator_rating * CO2_scrubber_rating;
	std::cout << "count " << count;
}