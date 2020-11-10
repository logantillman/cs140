// hflip.cpp
// Lab 2
// CS 140
// Author: Logan Tillman
// Date: September 9, 2019
// This program takes a pgm file and flips it horizontally

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

	// Checks the filetype
	if (filetype != "P2")
	{
		fprintf(stderr, "Bad PGM file -- first word is not P2\n");
		return 1;
	}

	// Checks to see if rows is valid
	if (!rows || (rows < 0))
    {
        fprintf(stderr, "Bad PGM file -- No row specification\n");
        return 1;
    }

	// Checks to see if columns is valid
	if (!columns || (columns < 0))
	{
		fprintf(stderr, "Bad PGM file -- No column specification\n");
		return 1;
	}

	// Checks to see if 255 follows the rows and columns 
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

	printf("%s\n%d %d\n%d\n", filetype.c_str(), columns, rows, alpha);

	// Prints the file in the correct format
	for (int i = 1; i < (rows+1); ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			// Prints out the row in reverse
			int a = (((columns*i) - j) - 1);

			// Checks to see if the pixel is a valid number
			if ((pixels[a] > 255) || (pixels[a] < 0))
			{
				fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", a);
				return 1;
			}

			cout << pixels[a] << " ";
		}	
		cout << '\n';
	}

	return 0;
}
