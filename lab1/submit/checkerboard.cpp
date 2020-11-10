// checkerboard.cpp
// CS 140
// This program takes 5 parameters and prints out a checkerboard based on the inputs
// Author: Logan Tillman
// 08-28-19 

#include <iostream>
using namespace std;

int main()
{
	int rows, columns, cycleSize, width;
	char startChar;

	// Error message for incorrect parameters 
	if (!(cin >> rows >> columns >> startChar >> cycleSize >> width))
		cerr << "usage: checkerboard  - stdin should contain R, C, SC, CS and W\n";

	// Silent exit error message
	if (rows <= 0 || columns <= 0 || cycleSize <= 0 || width <= 0 || (startChar + cycleSize) > 127)
		return -1;

	/* i and j loops are for outputting the normal rows and columns
	   k and l loops are for taking into account the width variable
	   for the rows and columns */
	for(int i = 0; i < rows; i++)
	{
		for(int k = 0; k < width; k++)
		{
			for(int j = 0; j < columns; j++)
			{
				for(int l = 0; l < width; l++)
				{
					cout << (char) (startChar + (i + j) % cycleSize);
				}
			}
			cout << '\n';
		}
	}

return 0;
}
