
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


struct Digit
{
	void PassChar(char InChar)
	{
		Characters++;
	}

	bool IsDigit()
	{
		//	//cout << DigitName << " IsDigit: Invalid " << Invalid << " Characters " << Characters << " RequiredCharacters Size " << RequiredCharacters.size() << "\n";
		return Characters == RequiredCharacters;
	}
	string DigitName;
	int RequiredCharacters = 0;

	int Characters = 0;
};

struct DigitOne : public Digit
{
	DigitOne()
	{
		RequiredCharacters = 2;
		DigitName = "Digit One";
	}
};

struct DigitFour : public Digit
{
	DigitFour()
	{
		RequiredCharacters = 4;
		DigitName = "Digit Four";
	}
};

struct DigitSeven : public Digit
{
	DigitSeven()
	{
		RequiredCharacters = 3;
		DigitName = "Digit Seven";
	}
};

struct DigitEight : public Digit
{
	DigitEight()
	{
		RequiredCharacters = 7;
		DigitName = "Digit Eight";
	}
};

bool IsDigit(string InSegment)
{
	vector<Digit> digits = { DigitOne(), DigitFour(),DigitSeven(), DigitEight() };
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
			return true;
	}

	return false;
}

int main()
{
	ifstream myfile;
	string string;
	myfile.open("list.txt");

	char comma = ',';
	int digits_appear = 0;
	int four_strings = 0;
	bool metLine = false;
	if (myfile.is_open())
	{
		while (myfile.good())
		{
			myfile >> string;

			if (string == "|")
			{
				cout << string << " ";
				cout << "\n";
				four_strings = 0;
				metLine = true;

				continue;
			}

			if (metLine)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

				if (IsDigit(string))
				{
					SetConsoleTextAttribute(hConsole, 2);
					cout << string << " ";
					digits_appear++;
				}
				else
				{
					SetConsoleTextAttribute(hConsole, 4);
					cout << string << " ";
				}
				SetConsoleTextAttribute(hConsole, 15);
				//return 0;
				four_strings++;
				if (four_strings == 4)
				{
					cout << "\n";
					four_strings = 0;
					metLine = false;
				}
			}
			else
			{
				cout << string << " ";
			}
		}
	}
	cout << "\n";
	cout << "digits appear " << digits_appear;
	cin.ignore();
}