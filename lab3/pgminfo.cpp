// pgminfo.cpp
// Lab 2
// CS 140
// Author: Logan Tillman
// Date: September 9, 2019
// This program takes in a pgm file and prints the file information to stdout

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

int main()
{
	string filetype;
	int columns, rows, alpha, numpix, pix;
	double total = 0;
	double avgpix;
	vector <int> pixels;

	cin >> filetype;

	// Checks filetype
	if (filetype != "P2")
	{
		fprintf(stderr, "Bad PGM file -- first word is not P2\n");
		return -1;
	}

	cin >> columns >> rows >> alpha;

	// Checks to make sure columns and rows are valid numbers
	if ((columns < 0) || (rows < 0))
		{
		fprintf(stderr, "Bad PGM file -- No row specification\n");
		return -1;
	}

	// Checks to make sure 255 follows column and row specification
	if (alpha != 255)
	{
		fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
		return -1;
	}
	
	// numpix = number of pixels the file should contain
	numpix = columns * rows;

		// Reads in the pixels
		while (cin >> pix)
			pixels.push_back(pix);
		
		// Checks the number of pixels in the file
		if (numpix != pixels.size())
		{
			fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
			return -1;
		}

		// Checks to make sure all the pixels are valid numbers
		for (int i = 0; i < pixels.size(); i++)
		{
			if ((pixels[i] < 0) || (pixels[i] > 255))
			{
				fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i);
				return -1;
			}

			// Running totals the pixels in the file
			total += pixels[i];
		}
		
		// Takes the average of all the pixels in the file
		avgpix = total / pixels.size();

		printf("# Rows: %11d\n", rows);
		printf("# Columns: %8d\n", columns);
		printf("# Pixels: %9d\n", numpix);
		printf("Avg Pixel: %8.3f\n", avgpix);

	return 0;
}
