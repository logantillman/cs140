// bitmatrix.cpp
// Lab 5
// CS140
// Author: Logan Tillman
// Date: October 7, 2019
// This lab performs operations to manipulate bit matrices

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include "bitmatrix.hpp"
using namespace std;

Bitmatrix::Bitmatrix(int rows, int cols)
{
	if (rows <= 0) 
	{
		const string s = "Bad rows";	
		throw (s);
		return;
	}
	if (cols <= 0)
	{
		const string s = "Bad cols";	
		throw (s);
		return;
	}
	
	// Resizing the vector to the parameters passed in
	M.resize(rows);
	
	for (unsigned int i = 0; i < M.size(); i++)
		M[i].resize(cols, '0');
}
           
Bitmatrix::Bitmatrix(const string &fn)
{
	ifstream file;
	string temp;
	string nspace;

	// Opening the file
	file.open(fn.c_str());

	if(file.fail()) 
	{
		const string s = "Can't open file";
		throw(s);
		file.close();
		return;
	}

	// Reads a line from the file and stores it in temp
	while (getline(file, temp))
	{
		nspace.clear();

		for (unsigned int i = 0; i < temp.size(); i++)
		{
			// Removing the spaces from temp and storing the characters in nspace
			if (temp[i] == '0' || temp[i] == '1')
				nspace.push_back(temp[i]);

			// Checks to see if there are any characters that aren't '1', '0', or ' '
			else if (temp[i] != ' ')
			{
				const string s = "Bad file format";
				throw(s);
				file.close();
				return;
			}
		}

		// Checks to see if all of the rows are > 0, and are the same size
		if ((M.size() > 0) && (temp.size() > 0) && (nspace.size() != M[0].size()))
		{
			const string s = "Bad file format";
			throw(s);
			file.close();
			return;
		}

		// Adds the string without spaces to the vector
		else if (temp.size() > 0)
			M.push_back(nspace);
	}

	file.close();
}
        
Bitmatrix *Bitmatrix::Copy() const
{
	Bitmatrix *cp;
	
	// Resizing the new bitmatrix to the current vector size
	cp = new Bitmatrix(M.size(), M[0].size());

	// Copying the data to the new bitmatrix
	for (unsigned int i = 0; i < M.size(); i++)
	{
		for (unsigned int j = 0; j < M[i].size(); j++)
			cp->Set(i, j, M[i][j]);
	}
	return cp;
}
                 
bool Bitmatrix::Write(const string &fn) const
{
	ofstream file;
	
	file.open(fn.c_str());

	if (file.fail()) 
		return false;

	// Writing each row to the file on it's own line
	for (unsigned int i = 0; i < M.size(); i++)
	{
		for (unsigned int j = 0; j < M[0].size(); j++)
			file << M[i][j];

		file << '\n';
	}

  return true;
}
 
void Bitmatrix::Print(size_t w) const
{
	unsigned int rows = M.size();
	unsigned int cols = M[0].size();

		// Printing out each row and column
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < cols; j++)
			{
				// Adding a space if w amount of columns have been printed
				if ((w > 0) && ((j % w) == 0) && (j > 0))
					printf(" ");

				printf("%c", M[i][j]);
			}
			printf("\n");

			// Printing an empty line if w amount of rows have been printed
			if (w > 0)
				if ((((i+1) % w) == 0) && ((i+1) != rows))
					printf("\n");
		}
}
                 
bool Bitmatrix::PGM(const string &fn, int p, int border) const
{
	vector < vector <int> > pixels;
	ofstream file;
	int rowresize;
	int colresize;

	// Calculating the amount of rows and columns to resize to
	rowresize = (((M.size() + 1) * border) + (p * M.size()));
	colresize = (((M[0].size() + 1) * border) + (p * M[0].size()));

	file.open(fn.c_str());

	if (file.fail())
		return false;
	if (p <= 0)
		return false;
	if (border < 0)
		return false;

	// Resizing the rows and columns
	pixels.resize(rowresize);

	for (unsigned int i = 0; i < pixels.size(); i++)
		pixels[i].resize(colresize, 0);

	// Printing the PGM file header
	file << "P2\n";
	file << pixels[0].size() << " " << pixels.size() << '\n';
	file << "255\n";

	// Looping through our rows
	for (unsigned int r = 0; r < M.size(); r++)
	{
		// These are the pixels we're trying to place from the
		// original bitmatrix
		for (int i = 0; i < p; i++)
		{
			// Looping through our columns
			for (unsigned int c = 0; c < M[0].size(); c++)
			{
				int rborder;
				int cborder;

				// Gives us an offset for the border
				// to find where our original numbers go
				rborder = (r * p) + (r * border) + border;
				cborder = (c * p) + (c * border) + border;

				// Placing the original numbers in the correct spot
				// in the new matrix and using the new values
				for (int j = 0; j < p; j++)
				{
					if (M[r][c] == '0')
						pixels[i+rborder][j+cborder] = 255;

					else if (M[r][c] == '1')
						pixels[i+rborder][j+cborder] = 100;
				}
			}
		}	
	}

	// Writing all of the pixels to the pgm file
	for (unsigned int i = 0; i < pixels.size(); i++)
	{
		for (unsigned int j = 0; j < pixels[0].size(); j++)
			file << pixels[i][j] << " ";
		
		file << '\n';
	}

	file.close();

  return true;
}

int Bitmatrix::Rows() const
{
  // Returning the amount of rows in the vector
  return M.size();
}
                            
int Bitmatrix::Cols() const
{
  // Returning the amount of columns in the vector
  return M[0].size();
}
                            
char Bitmatrix::Val(int row, int col) const
{
	// Returns the character value at the given row
	// and column if the parameters are valid
	if (row < 0 || row >= (int) M.size())
		return 'x';
	else if (col < 0 || col >= (int) M[0].size())
		return 'x';
	else
		return M[row][col];
}
            
bool Bitmatrix::Set(int row, int col, char val)
{
	// Makes sure the row, column, and value variables are valid
	if (row < 0 || row >= (int) M.size()) 
		return false;
	if (col < 0 || col >= (int) M[0].size()) 
		return false;
	if (val != '0' && val != '1') 
		return false;
	
	// Sets the value at the given row and column
	// to the value passed in as a parameter
	else
	{
		M[row][col] = val;
		return true;
	}
}
        
bool Bitmatrix::Swap_Rows(int r1, int r2)
{
	string temp;

	// Makes sure the rows are valid
	if (r1 < 0 || r1 >= (int) M.size()) 
		return false;
	if (r2 < 0 || r2 >= (int) M.size()) 
		return false;

	// Swaps r1 and r2 by storing one in a temp variable
	temp = M[r1];
	M[r1] = M[r2];
	M[r2] = temp;

  return true;
}
              
bool Bitmatrix::R1_Plus_Equals_R2(int r1, int r2)
{
	stringstream ss;

	// Checks to see if the rows are valid
	if (r1 < 0 || r1 >= (int) M.size()) 
		return false;
	if (r2 < 0 || r2 >= (int) M.size()) 
		return false;

	else
	{
		// Sets r1 equal to the sum of r1 and r2
		for (unsigned int i = 0; i < M[0].size(); i++)
		{
			int sum;

			sum = (M[r1][i] + M[r2][i]) % 2;
			M[r1][i] = sum + '0';
		}
		return true;
	}
}     

// This is the hash function used to index the hash table
unsigned int djb_hash(const string &s)
{
  size_t i;
  unsigned int h;
  
  h = 5381;

  for (i = 0; i < s.size(); i++) {
    h = (h << 5) + h + s[i];
  }
  return h;
}

Bitmatrix *Sum(const Bitmatrix *a1, const Bitmatrix *a2)
{
	unsigned int a1rows, a1cols;
	unsigned int a2rows, a2cols;
	Bitmatrix *bitsum;

	a1rows = a1->Rows();
	a1cols = a1->Cols();
	a2rows = a2->Rows();
	a2cols = a2->Cols();
	bitsum = new Bitmatrix(a1rows, a1cols);

	// Checks to make sure the rows and columns are equal size
	if (a1rows != a2rows && a1cols != a2cols)
		return NULL;

	for (int i = 0; i < bitsum->Rows(); i++)
	{
		for (int j = 0; j < bitsum->Cols(); j++)
		{
			char val;
	
			// This uses % 2 to calculate the result of the addition
			val = (a1->Val(i, j) + a2->Val(i, j)) % 2;

			// Adding character 0 to turn the int value into a char
			val += '0';

			// Setting the result in the new bitmatrix
			bitsum->Set(i, j, val);
		}
	}
	return bitsum;
}

Bitmatrix *Product(const Bitmatrix *a1, const Bitmatrix *a2)
{
	Bitmatrix *prod;

	// Creating a new bitmatrix with the amount of rows in a1
	// and the amount of columns in a2. This is because product
	// is going to use the dot product
	prod = new Bitmatrix(a1->Rows(), a2->Cols());

	// Checking to make sure the two bitmatrices are eligible
	// to be multiplied
	if (a1->Cols() != a2->Rows())
		return NULL;
	
	for (int i = 0; i < a1->Rows(); i++)
	{
		for (int j = 0; j < a2->Cols(); j++)
		{
			int dotproduct;

			dotproduct = 0;

			// Calculating the dot product for the two values
			for (int k = 0; k < a1->Cols(); k++)
				dotproduct = dotproduct + (a1->Val(i, k) * a2->Val(k, j));

			// Transforming the value into a char so we can store it
			prod->Set(i, j, ((dotproduct % 2) + '0'));
		}
	}
	
  return prod;
}

Bitmatrix *Sub_Matrix(const Bitmatrix *a1, const vector <int> &rows)
{
	Bitmatrix *sub;

	// Creating a new bitmatrix to use for our sub
	sub = new Bitmatrix(rows.size(), a1->Cols());

	// Checks to see if the row vector is valid
	if (rows.size() == 0)
		return NULL;

	for (unsigned int i = 0; i < rows.size(); i++)
	{
		// Checks to the if the row inside if the vector exists
		if (rows[i] >= a1->Rows())
			return NULL;

		// Sets the value in the sub matrix to the value at the given
		// row in the original matrix
		for (int j = 0; j < a1->Cols(); j++)
			sub->Set(i, j, a1->Val(rows[i], j));
	}

  return sub;
}

Bitmatrix *Inverse(const Bitmatrix *m)
{
	Bitmatrix *inv;
	Bitmatrix *mcopy;

	// inv is the inverse matrix and mcopy is the
	// identity matrix
	inv = new Bitmatrix(m->Rows(), m->Cols());
	mcopy = m->Copy();

	// Setting the inverse to match the picture in the write up
	for (int i = 0; i < m->Rows(); i++)
		inv->Set(i, i, '1');

	for (int i = 0; i < mcopy->Rows(); i++)
	{
		// Checking to see if the value at i is '0'
		if (mcopy->Val(i, i) != '1')
		{
			// Loops through all the rows greater than i
			for (int j = i+1; j < mcopy->Rows(); j++)
			{
				// Once it finds a row that = '1', it swaps them
				if (mcopy->Val(j, i) == '1')
				{
					mcopy->Swap_Rows(i, j);
					inv->Swap_Rows(i, j);
					break;
				}
			}
			
			// If it doesn't find a row that equals '1', the matrix
			// isn't invertible
			if (mcopy->Val(i, i) != '1')
				return NULL;
		}
		
		// This loop does the += operation if the 
		// copy at [j][i] is equal to '1'
		for (int j = i+1; j < mcopy->Rows(); j++)
		{
			if (mcopy->Val(j, i) == '1')
			{
				mcopy->R1_Plus_Equals_R2(j, i);
				inv->R1_Plus_Equals_R2(j, i);
			}
		}
	}

	// Looping through the rows backwards
	for (int i = mcopy->Rows()-2; i >= 0; i--)
	{
		for (int j = mcopy->Rows()-1; j > 0; j--)
		{
			// If the row at [i][j] is 1 and j is greater than
			// i, then it'll += the two and store the value in row i
			if ((mcopy->Val(i, j) == '1') && (j > i))
			{
				mcopy->R1_Plus_Equals_R2(i, j);
				inv->R1_Plus_Equals_R2(i, j);
			}
		}
	}

  return inv;
}

BM_Hash::BM_Hash(int size)
{
	if (size <= 0)
	{
		const string s = "Bad size";
		throw(s);
		return;
	}
	
	// Resizing the table to the passed in size parameter
	Table.resize(size);
}

bool BM_Hash::Store(const string &key, Bitmatrix *bm)
{
	unsigned int index;
	unsigned int tablesize;
	HTE *entry;

	// Checking to see if the table exists
	if (Table.size() == 0)
		return false;

	// Calculating the index for the table
	index = djb_hash(key);
	index = index % Table.size();

	// Creating a tablesize vector to clean up my for loops
	tablesize = Table[index].size();

	// Creating a new entry to add to the hash table
	entry = new HTE;
	entry->bm = bm;
	entry->key = key;

	// Checks to see if the key already exists in the table
	for (unsigned int i = 0; i < tablesize; i++)
	{
		if(Table[index][i].key == key)
			return false;
	}
	
	// If it's a new key, it adds it to the table
	Table[index].push_back(*entry);

  return true; 
}
    
Bitmatrix *BM_Hash::Recall(const string &key) const
{
	unsigned int index;
	unsigned int tablesize;

	// Checks to see if the table exists
	if (Table.size() == 0)
		return NULL;

	// Calculates the index for the hash table
	index = djb_hash(key);
	index = index % Table.size();
	
	// Once again, this variable cleans up my loop
	tablesize = Table[index].size();

	for (unsigned int i = 0; i < tablesize; i++)
	{
		// Finds the key in the table and returns the bitmatrix
		if (Table[index][i].key == key)
			return Table[index][i].bm;
	}

  return NULL;
}
      
vector <HTE> BM_Hash::All() const
{
  vector <HTE> rv;

	for (unsigned int i = 0; i < Table.size(); i++)
	{
		for (unsigned int j = 0; j < Table[i].size(); j++)
			// Adding the values in the hash table to the rv vector
			rv.push_back(Table[i][j]);
	}

  return rv;
}
