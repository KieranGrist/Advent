
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

struct LineSegment
{

	bool SegmentComplete()
	{
		return  x1 != -1 && y1 != -1 && x2 != -1 && y2 != -1;
	}

	void Print()
	{
		std::cout << "x1 " << x1 << ", ";
		std::cout << "y1 " << y1 << ", ";
		std::cout << "x2 " << x2 << ", ";
		std::cout << "y2 " << y2 << "\n";
	}
	void AddNumber(int InNumber)
	{
		if (x1 == -1)
		{
			x1 = InNumber;
			//	std::cout << "x1 " << x1 << "\n";
			return;
		}

		if (y1 == -1)
		{
			y1 = InNumber;
			//	std::cout << "y1 " << y1 << "\n";
			return;
		}

		if (x2 == -1)
		{
			x2 = InNumber;
			//	std::cout << "x2 " << x2 << "\n";
			return;
		}

		if (y2 == -1)
		{
			y2 = InNumber;
			//	std::cout << "y2 " << y2 << "\n";
			return;
		}
	}
	int x1 = -1;
	int y1 = -1;
	int x2 = -1;
	int y2 = -1;
};

struct GridPoint
{
	GridPoint(int InX, int InY)
	{
		X = InX;
		Y = InY;
	}
	void Print()
	{
		std::cout << LinesCoveringPoint << " ";
	}

	int X = -1;
	int Y = -1;
	int LinesCoveringPoint = 0;
};


struct Grid
{
	/*
	My basic thought on this is that we we have a grid point x0 y0
	we form the grid dynamically, when a point intersects/matches with x0 y0 we increase the number
	so then x0 y0 becomes 1
	*/

	void Print()
	{
		int count = 0;

		for (auto itr = MappedGridPoints.begin(); itr != MappedGridPoints.end(); itr++)
		{
			count += itr->second.LinesCoveringPoint >= 2 ? 1 : 0;
		}

		for (int y = 0; y <= HighestY; y++)
		{
			for (int x = 0; x <= HighestX; x++)
			{
				auto grid_point = CreateOrFindPoint(x, y);
			//	grid_point->second.Print();
			}
			//std::cout << "\n";
		}

		std::cout << "Mapped Grid Points " << MappedGridPoints.size() << " Lines Covering " << count << "\n";
	}

	std::map<std::string, GridPoint>::iterator CreateOrFindPoint(int InX, int InY)
	{
		std::string point = "x" + std::to_string(InX) + ", y" + std::to_string(InY);
		auto grid_point = MappedGridPoints.find(point);
		if (grid_point != MappedGridPoints.end())
			return grid_point;
		MappedGridPoints.insert(std::pair<std::string, GridPoint>(point, GridPoint(InX, InY)));
		return MappedGridPoints.find(point);
	}

	void CreateGrids()
	{
		// Add any grids to the map 
		for (int y = LowestY; y <= HighestY; y++)
		{
			for (int x = LowestX; x <= HighestX; x++)
			{
				CreateOrFindPoint(x, y);
			}
		}
	}

	void AddLineSegment(LineSegment InSegment)
	{
		// for now ensure it is a line 
		bool is_line = false;
		if (InSegment.x1 == InSegment.x2 || InSegment.y1 == InSegment.y2)
			is_line = true;

		if (!is_line)	
			return;

		int x_start = std::min(InSegment.x1, InSegment.x2);
		int x_end = std::max(InSegment.x1, InSegment.x2);

		int y_start = std::min(InSegment.y1, InSegment.y2);
		int y_end = std::max(InSegment.y1, InSegment.y2);
		for (int y = y_start; y <= y_end; y++)
		{
			for (int x = x_start; x <= x_end; x++)
			{
				auto grid_point = CreateOrFindPoint(x, y);
				grid_point->second.LinesCoveringPoint++;
			}
		}
	}

	void HandleHighestAndLowest(LineSegment InSegment)
	{
		HighestX = std::max(HighestX, InSegment.x1);
		HighestX = std::max(HighestX, InSegment.x2);
		LowestX = std::min(LowestX, InSegment.x1);
		LowestX = std::min(LowestX, InSegment.x2);

		HighestY = std::max(HighestY, InSegment.y1);
		HighestY = std::max(HighestY, InSegment.y2);
		LowestY = std::min(LowestY, InSegment.y1);
		LowestY = std::min(LowestY, InSegment.y2);
	}

	int HighestX = -1;
	int LowestX = 1000000;

	int HighestY = -1;
	int LowestY = 1000000;
private:
	std::map<std::string, GridPoint> MappedGridPoints;
};

int main()
{
	std::ifstream myfile;
	std::string string;
	myfile.open("list.txt");
	std::vector<LineSegment> LineSegments;
	char comma = ',';

	if (myfile.is_open())
	{
		LineSegment line_segment;
		while (myfile.good())
		{
			myfile >> string;
			//std::cout << string << "\n";

			std::string coordinate_string;
			while (string.size() > 0 && string != "->")
			{
				auto itr = string.begin();
				char number = *itr;
				coordinate_string.push_back(number);
				if (*itr == comma)
				{
					int num = std::stoi(coordinate_string);
					//std::cout << "coordinate_string " << num << "\n";
					line_segment.AddNumber(num);
					coordinate_string.clear();
				}
				string.erase(itr);
				if (string.size() == 0)
				{
					int num = std::stoi(coordinate_string);
					//std::cout << "coordinate_string " << num << "\n";
					line_segment.AddNumber(num);
					coordinate_string.clear();
				}
			}

			if (line_segment.SegmentComplete())
			{	
				LineSegments.push_back(line_segment);
				line_segment = LineSegment();
			}
		}
	}

	Grid grid;

	for (auto segment : LineSegments)
	{
		grid.HandleHighestAndLowest(segment);
	}

	grid.CreateGrids();

	for (auto segment : LineSegments)
	{
		segment.Print();
		grid.AddLineSegment(segment);
	}
	grid.Print();
}