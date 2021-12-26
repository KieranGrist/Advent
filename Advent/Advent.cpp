
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
#include <windows.h>   // WinApi header

using namespace std;

const char a = 'a';
const char b = 'b';
const char c = 'c';
const char d = 'd';
const char e = 'e';
const char f = 'f';
const char g = 'g';


struct Digit
{
public:

	void PassChar(char InChar)
	{
		if (find(RequiredCharacters.begin(), RequiredCharacters.end(), InChar) != RequiredCharacters.end())
		{
			Characters++;
		}
		else
		{
			Invalid = true;
		}
			
	}

	bool IsDigit()
	{
		if (Invalid)
			return false;
	
		return Characters == RequiredCharacters.size();
	}
	string DigitName;
	std::vector<char> RequiredCharacters;

	int Characters = 0;

	char Num = '-';

	bool Invalid = false;
};

struct DigitZero : public Digit
{
	DigitZero()
	{
		RequiredCharacters = { c,a,g,e,d,b };
		DigitName = "Digit Zero";
		Num = '0';
	}
};
struct DigitOne : public Digit
{
	DigitOne()
	{
		RequiredCharacters = { a, b };
		DigitName = "Digit One";
		Num = '1';
	}
};

struct DigitTwo : public Digit
{
	DigitTwo()
	{
		RequiredCharacters = { g,c,d,f, a };
		DigitName = "Digit Two";
		Num = '2';
	}
};

struct DigitThree : public Digit
{
	DigitThree()
	{
		RequiredCharacters = { f,b,c,a,d };
		DigitName = "Digit Three";
		Num = '3';
	}
};

struct DigitFour : public Digit
{
	DigitFour()
	{
		RequiredCharacters = { e,a,f,b };
		DigitName = "Digit Four";
		Num = '4';
	}
};

struct DigitFive : public Digit
{
	DigitFive()
	{
		RequiredCharacters = { c,d,f,b,e };
		DigitName = "Digit Five";
		Num = '5';
	}
};

struct DigitSix : public Digit
{
	DigitSix()
	{
		RequiredCharacters = { c,d,f,g,e,b };
		DigitName = "Digit Six";
		Num = '6';
	}
};

struct DigitSeven : public Digit
{
	DigitSeven()
	{
		RequiredCharacters = { d,a,b };
		DigitName = "Digit Seven";
		Num = '7';
	}
};

struct DigitEight : public Digit
{
	DigitEight()
	{
		RequiredCharacters = { a,c,e,d,g,f,b };
		DigitName = "Digit Eight";
		Num = '8';
	}
};

bool IsDigit(string InSegment, Digit& OutDigit)
{
	vector<Digit> digits = { DigitZero(), DigitOne(), DigitFour(),DigitSeven(), DigitEight()};
	for (auto digit = digits.begin(); digit != digits.end(); digit++)
	{
		for (char current_char : InSegment)
		{
			digit->PassChar(current_char);
		}
	}

	////cout << "\n";
	for (auto digit = digits.begin(); digit != digits.end(); digit++)
	{
		if (digit->IsDigit())
		{
			Digit a = *digit;
			OutDigit = a;
			return true;
		}
	}

	return false;
}

int main()
{
	ifstream myfile;
	string file_string;
	myfile.open("list.txt");

	char comma = ',';
	int digits_appear = 0;
	int four_strings = 0;
	bool metLine = false;
	string output_value;

	if (myfile.is_open())
	{
		while (myfile.good())
		{
			myfile >> file_string;

			if (file_string == "|")
			{
				cout << file_string << " ";
				cout << "\n";
				four_strings = 0;
				metLine = true;
				output_value = "";
				continue;
			}

			if (metLine)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

				Digit digit;
				if (IsDigit(file_string, digit))
				{
					SetConsoleTextAttribute(hConsole, 2);
			
					cout << digit.Num << " ";
					output_value.push_back(digit.Num);
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 4);
					cout << file_string << " ";
				}
				SetConsoleTextAttribute(hConsole, 15);
				four_strings++;
				if (four_strings == 4)
				{
					if (output_value != "")
					{
					
					int value = stoi(output_value);
					digits_appear += value;
					cout << value;
					}
					cout << "\n";
					four_strings = 0;
					metLine = false;
				}
			}
			else
			{
				cout << file_string << " ";
			}

		}
	}
	cout << "\n";
	cout << "digits appear " << digits_appear;
	cin.ignore();
}