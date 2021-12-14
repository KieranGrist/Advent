
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

struct BingoBoard
{
public:
	BingoBoard()
	{
		Board.clear();
	}

	void AddNumber(int InNumber)
	{
		for (int i = 0; i < 5; i++)
		{
			auto size = Board[i].size();
			if(size == 5)
				continue;
			Board[i].push_back(InNumber);
			return;
		}
	}
	
	void AddBingoNumber(int InNumber)
	{
		Numbers.push_back(InNumber);
	}

	bool NumbersContains(int InNumber)
	{
		for (auto itr : Numbers)
		{
			if (itr == InNumber)
			{
				return true;
			}
		}
		return false;
	}

	bool HasWon(std::vector<int>& WinningNumbers)
	{
		// Row check 
		std::map<int, std::vector<int>> column;
		for (auto itr = Board.begin(); itr != Board.end(); ++itr)
		{
			auto row_numbers = itr->second;
			int count =0;
			int row = 0;
			for (auto num : row_numbers)
			{
				if (NumbersContains(num))
				{
					column[row].push_back(num);
					count++;
				}
				row++;
			}
			if (count == 5)
			{
				WinningNumbers = row_numbers;
				return true;
			}
			
		}
		for (auto itr = column.begin(); itr != column.end(); ++itr)
		{
			auto column_numbers = itr->second;
			if (column_numbers.size() == 5)
			{
				WinningNumbers = column_numbers;
				return true;
			}
		}
		return false;
	}

	void Print()
	{
		std::cout << "board " << Index << "\n";
		for (auto itr = Board.begin(); itr != Board.end(); ++itr)
		{
			auto row_numbers = itr->second;
			size_t size = row_numbers.size();
			for (int i =0; i <= size; i++)
			{
				if (i == size)
				{
					std::cout << "\n";
					continue;
				}

				auto num = row_numbers[i];
				if (NumbersContains(num))
				{
					std::cout << "pass " << num << "\t";
	
				}
				else
				{
					std::cout << "fail " << num << "\t";
				}
			}
		}
	}


	int Sum()
	{
		int sum = 0;
		for (auto itr = Board.begin(); itr != Board.end(); ++itr)
		{
			for (auto num : itr->second)
			{		
				if (!NumbersContains(num))
				{
					std::cout << sum <<" + " << num << " = " << sum + num << "\n";;
					sum += num;
				}
			}
		}
		return sum;
	}

	int NumbersCount()
	{
		int size = 0;
		for (int i = 0; i < 5; i++)
		{
			int row_size = Board[i].size();
		//	std::cout << "row_size " << row_size << "\n";
			size += row_size;
		}
		//std::cout << "number count " << size << "\n";
		return size;
	}

	int Index = 0;

private:
	std::map<int, std::vector<int>> Board;
	
	std::vector<int> Numbers;

};

int main()
{
	std::ifstream myfile;
	std::string bingo_string;
	myfile.open("list.txt");
	std::vector<int> bingo_numbers;
	std::vector<BingoBoard> bingo_boards;
	int Index = 0;
	if (myfile.is_open())
	{
		BingoBoard current_board;
		while (myfile.good())
		{
			myfile >> bingo_string;
			//std::cout << "bingo_string " << bingo_string << "\n";

			if (bingo_numbers.size() == 0)
			{
				std::string bingo_number_string;
				while (bingo_string.size() > 0)
				{
					auto itr = bingo_string.begin();
					char number = *itr;
					bingo_number_string.push_back(number);
					char comma = ',';
					if (*itr == comma)
					{
						int num = std::stoi(bingo_number_string);
						//std::cout << "bingo number " << num << "\n";
						bingo_numbers.push_back(num);
						bingo_number_string.clear();
					}
					bingo_string.erase(itr);
				}
			}
			else
			{
				current_board.AddNumber(std::stoi(bingo_string));
				if (current_board.NumbersCount() == 25)
				{
					bingo_boards.push_back(current_board);
					current_board = BingoBoard();
					current_board.Index = Index;
					Index++;
				}
			}
		}
	}

	
	BingoBoard winning_board;
	int wining_number = -1;
	for (auto num : bingo_numbers)
	{
		std::cout << "number " << num << "\n";
		for (BingoBoard& board : bingo_boards)
		{
			board.AddBingoNumber(num);
			board.Print();
			std::cout << "\n";
			std::vector<int> WinningNumbers;
			if (board.HasWon(WinningNumbers))
			{
				wining_number = num;
				winning_board = board;
				break;
			}
		}
		if (wining_number!= -1)
			break;
	}
	std::cout << "Wining Number " << wining_number <<"\n"  ;
	int score = winning_board.Sum() * wining_number;
	std::cout << "score " << score << "\n";;
}