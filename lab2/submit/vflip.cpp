// vflip.cpp
// Lab 2
// CS 140
// Author: Logan Tillman
// Date: September 9, 2019
// This program takes a pgm file and flips it vertically

#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

vector <int> vflip (vector <int> pixels, int rows, int columns, int col);

int main()
{
	string filetype;
	int columns, rows, alpha, numpix, pix;
	int count = 0;
	vector <int> pixels;

	cin >> filetype;

	// Checks the filetype
	if (filetype != "P2")
	{
		fprintf(stderr, "Bad PGM file -- first word is not P2\n");
		return 1;
	}

	cin >> columns >> rows >> alpha;

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

	// Checks to see if 255 follows rows and columns in file
	if (alpha != 255)
	{
		fprintf(stderr, "Bad PGM file -- No 255 following the rows and columns\n");
		return 1;
	}
	
	// numpix = total number of pixels supposed to be in the pgm
	numpix = columns * rows;

	// Fills the vector
	while (cin >> pix)
		pixels.push_back(pix);
		
	// Checks to see if the size of the vector is correct
	if (numpix != pixels.size())
	{
		fprintf(stderr, "Bad PGM file -- Extra stuff after the pixels\n");
		return -1;
	}

	// Checks to see if each pixel is a valid number
	for (int i = 0; i < pixels.size(); i++)
	{
		if ((pixels[i] < 0) || (pixels[i] > 255))
		{
			fprintf(stderr, "Bad PGM file -- pixel %d is not a number between 0 and 255\n", i);
			return -1;
		}
	}
	
	printf("%s\n%d %d\n%d\n", filetype.c_str(), columns, rows, alpha);

	// Calls vflip for each column to flip the vector
	for (int col = 0; col < columns; col++)
	{
		pixels = vflip(pixels, rows, columns, col);		
	}

	// Prints out the pgm in the correct format
	for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            cout << pixels[count] << " ";
			++count;
        }
        cout << '\n';
    }

	return 0;
}

// Flips each column vertically
vector <int> vflip (vector <int> pixels, int rows, int columns, int col)
{
    int temp;

	// Loops through the top half of the pgm
    for (int i = 0; i < (rows/2); i++)
    {
		// a is one pixel on the top half
        int a = ((columns * i) + col);
		// b is a's corresponding pixel on the bottom half
        int b = ((((rows * columns) - columns) + col) - (i * columns));
     
		// Switches a and b using a temporary variable
		temp = pixels[a];
        pixels[a] = pixels[b];
        pixels[b] = temp;
    }
	return pixels;
} 
