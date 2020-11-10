// pgm.cpp
// Lab3
// CS140
// Author: Logan Tillman
// Date: September 15, 2019
// This lab modifies a pgm file based on the input

#include "pgm.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool Pgm::Read(const std::string &file)
{
  ifstream fin;
  string s;
  size_t i, j, r, c, v;

  fin.open(file.c_str());
  if (fin.fail()) return false;
  
  if (!(fin >> s)) return false;
  if (s != "P2") return false;
  if (!(fin >> c) || c <= 0) return false;
  if (!(fin >> r) || r <= 0) return false;
  if (!(fin >> i) || i != 255) return false;

  Pixels.resize(r);
  for (i = 0; i < r; i++) {
    Pixels[i].clear();
    for (j = 0; j < c; j++) {
      if (!(fin >> v) || v > 255) return false;
      Pixels[i].push_back(v);
    }
  }
  if (fin >> s) return false;
  fin.close();
  return true;
}

bool Pgm::Write(const std::string &file) const
{
	if (Pixels.size() == 0)
		return 0;

	ofstream fout;
	string s = "P2";
	const int r = Pixels.size();
	const int c = Pixels[0].size();
	int count = 0;

	fout.open(file.c_str());
	
	fout << s << '\n' << c << " " << r;
	fout << '\n' << 255 << '\n';

	for(int i = 0; i < (int) Pixels.size(); i++)
	{
		for(int j = 0; j < (int) Pixels[i].size(); j++)
		{
			// Checks to see if it's the 20th pixel to go to new line
			if (((count % 20) == 19))
				fout << Pixels[i][j] << '\n';

			// Checks to see if it's the last pixel in the file so it can 
			// go to a new line
			else if (count == ((int)(Pixels.size() * Pixels[i].size())-1))
				fout << Pixels[i][j] << '\n';

			// Else it just prints a space after the pixel
			else	
				fout << Pixels[i][j] << " ";
			++count;
		}	
	}

	fout.close();
	return 1;
}

bool Pgm::Create(size_t r, size_t c, size_t pv)
{
	if (pv > 255 || r == 0 || c == 0) 
		return 0;
	
	// Resizing the vector to [r][c] and filling in with pv
	Pixels.resize(r);

	for (int i = 0; i < (int) r; i++)
	{
		Pixels[i].resize(c);

		for (int j = 0; j < (int) c; j++)
			Pixels[i][j] = pv;
	}

	return 1;
}
 
bool Pgm::Clockwise()
{
	vector < vector <int> > Pixels2;
	
	const int r = Pixels.size();
	const int c = Pixels[0].size();

	// Resizing the temp vector to [c][r]
	Pixels2.resize(c);

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			Pixels2[j].resize(r);

			// Switching the rows in Pixels to columns in the temp
			Pixels2[j][i] = Pixels[i][j];
		}
	}

	// Changing Pixels vector to match the temp vector ([c][r])
	Pixels.resize(c);

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			Pixels[j].resize(r);

			// Flipping the rows backwards in the temp 
			// vector to finish the CW rotation
			Pixels[j][i] = Pixels2[j][(r-1)-i];
		}
	}

	return 1;
}

bool Pgm::Cclockwise()
{
	vector < vector <int> > Pixels2;
	const int r = Pixels.size();
	const int c = Pixels[0].size();

	// Resizing the temp to [c][r]
	Pixels2.resize(c);

	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			Pixels2[j].resize(r);
			
			// Takes the last column in Pixels
			// and makes it the first row in the
			// temp vector, which rotates it CCW
			Pixels2[j][i] = Pixels[i][(c-1)-j];
		}
	}

	// Copies the temp back to Pixels
	Pixels = Pixels2;
	
	return 1;
}

bool Pgm::Pad(size_t w, size_t pv)
{
	const int r = Pixels.size();
	const int c = Pixels[0].size();

	// Determines how many rows and cols to add
	const int addAmount = w * 2;

	if (pv > 255)
		return 0;

	Pixels.resize(r+addAmount);

	// Adding the padding to the vector
	for (int i = 0; i < (int) Pixels.size(); i++)
		Pixels[i].resize((c+addAmount), pv);

	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			int temp;
			const int row = r - i;
			const int col = c - j;

			// Moves the pgm pixels to the correct spot
			// starting with the bottom right pixel
			temp = Pixels[row+w][col+w];
			Pixels[row+w][col+w] = Pixels[row][col];
			Pixels[row][col] = temp;
		}
	}

	return 1;
}

bool Pgm::Panel(size_t r, size_t c)
{
	int imgr = Pixels.size();
	int imgc = Pixels[0].size();
	vector < vector<int> > Pixels2;

	if (r == 0 || c == 0)
		return 0;

	// Doing the copy to the temp vector before
	// panelling because it's smaller
	Pixels2 = Pixels;

	// Resizing to match the panel inputs
	Pixels.resize(r * imgr);

	for (int i = 0; i < (int) Pixels.size(); i++)
	{
		Pixels[i].resize(c * imgc);
	
		// Determining which pixel corresponds to the new
		// vector size depending on the current pixel %
		// to the row or column size of the original
		for (int j = 0; j < (int) Pixels[i].size(); j++)
			Pixels[i][j] = Pixels2[i%imgr][j%imgc];
	}

	return 1;
}

bool Pgm::Crop(size_t r, size_t c, size_t rows, size_t cols)
{
	// Checks if the parameters are in bounds
	if (((r+rows) > Pixels.size()) || ((c+cols) > Pixels[0].size()))
		return 0;

	for (int i = 0; i < (int) rows; i++)
	{
		// Moving the cropped picture to the top left
		// of the vector
		for (int j = 0; j < (int) cols; j++)
			Pixels[i][j] = Pixels[r+i][c+j];
	}

	// Resizing to match the crop
	Pixels.resize(rows);
	
	for (int i = 0; i < (int) rows; i++)
		Pixels[i].resize(cols);

	return 1;
}

