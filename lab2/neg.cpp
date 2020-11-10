// neg.cpp
// Lab 2
// CS 140
// Author: Logan Tillman
// Date: September 9, 2019
// This program takes a pgm file and returns the negative pgm of it

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	string filetype;
	int columns, rows, alpha, pix;
	int count = 0;
	vector <int> pixels;
		
	cin >> filetype;
	cin >> columns >> rows >> alpha;

	// Checks to make sure 255 follows the rows and columns
	if (alpha != 255)
	{
		fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
		return 1;
	}

	// Fills the vector
	while (cin >> pix)
	{
		cin.clear();
		pixels.push_back(pix);
	}

	// Checks the file size
	if ((rows*columns) != pixels.size())
	{
		fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
		return 1;
	}

	printf("%s\n%d %d\n%d\n", filetype.c_str(), columns, rows, alpha);

	// Subtracts the pixel value from 255 to get the negative pgm
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			printf("%d ", (255-pixels.at(count)));
			++count;
		}	
		cout << '\n';
	}

	return 0;
}
