// bigwhite.cpp
// Lab 2
// CS 140
// Author: Logan Tillman
// Date: September 9, 2019
// This program takes in two inputs, rows and columns, then creates
// a file in those dimensions filled with white pixels

#include <iostream>
#include <sstream>
#include <cstdio>
using namespace std;

int main(int argc, char *argv[])
{
	int rows;
	int columns;
	stringstream ss;

	// Inputs the command line arguments into a string stream to convert the types
	for (int i = 1; i < 3; i++)
	{
		ss << argv[i];
		
		if (i == 1)
			ss >> rows;
		if (i == 2)
			ss >> columns;
		
		ss.clear();
	}

	// Checks to make sure file was called correctly
	if ((rows <= 0) || (columns <= 0) || (argc != 3))
	{
		fprintf(stderr, "usage: bigwhite rows cols\n");
		return 1;
	}
	
	printf("P2\n%d %d\n%d\n", columns, rows, 255);

	// Fills the file with white pixels
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << "255 ";			
		}
		cout << '\n';
	}	


	return 0;	
}
