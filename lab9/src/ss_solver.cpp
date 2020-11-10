// ss_solver.cpp
// Lab 9
// CS 140
// Author: Logan Tillman
// Date: November 13, 2019

/*	This is a solver for the neopets game called ShapeShifter. This program
  	uses recursion to test all possibile positions for the shapes until it
 	finds a solution. If there is no solution, it won't print anything. */

#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
using namespace std;

class Shifter {
  public:
    bool Read_Grid_And_Shapes(int argc, const char **argv);
    bool Apply_Shape(int index, int r, int c);
    bool Find_Solution(int index);
    void Print_Solution() const;
  protected:
    vector <string> Grid;
    vector < vector <string> > Shapes;     
    vector <int> Solution_Rows;            
    vector <int> Solution_Cols;            
};

int main (int argc, const char **argv)
{
	Shifter *game;
	bool solvable;

	// Creates an instance of the shifter class
	game = new Shifter;

	/* Reads the grid and shapes using command 
	   line arguments and standard input */
	if(!(game->Read_Grid_And_Shapes(argc, argv)))
		return 1;

	// Checks if the game has a solution
	solvable = game->Find_Solution(0);

	// If it is solvable, we print the solution
	if (solvable == true)
		game->Print_Solution();

	delete game;
	return 0;
}

/* This function creates a Grid from the command line arguments
   and it will store the shapes read through standard input */
bool Shifter::Read_Grid_And_Shapes(int argc, const char **argv)
{
	stringstream ss;
	vector <string> vshapes;
	string shape;

	// Creating the grid
	for (int i = 1; i < argc; i++)
		Grid.push_back(argv[i]);

	// Reading in the shapes
	while (getline(cin, shape))
	{
		ss.clear();
		ss.str(shape);

		// Using a string stream to seperate the rows of the shape
		while(ss >> shape)
			vshapes.push_back(shape);

		// Adding the shape to the Shapes vector
		Shapes.push_back(vshapes);
		
		// Emptying the temporary vector
		vshapes.clear();
	}

	return true;
}

/* This function take the shape at Shapes[index]
   and applies it to Row r and Column c */
bool Shifter::Apply_Shape(int index, int r, int c)
{
	vector <string> s;

	/* Using a temporary vector to store the shape
	   so I can treat it as a 2d vector rather than 3d */
	s = Shapes[index];

	/* Checking to see if the shape will fit 
	   in the grid at Row r and Column c */
	if ((r+s.size()) > Grid.size())
		return false;
	if ((c+s[0].size()) > Grid[0].size())
		return false;

	// Applying the shape to the grid
	for (unsigned int i = 0; i < s.size(); i++)
	{
		for (unsigned int j = 0; j < s[i].size(); j++)
		{
			// XORing the shape with the grid using if statements
			if (s[i][j] == '1')
			{
				if (Grid[r+i][c+j] == '1')
					Grid[r+i][c+j] = '0';
				else if (Grid[r+i][c+j] == '0')
					Grid[r+i][c+j] = '1';
			}
		}
	}

	return true;
}

// Finds the solution to the game using recursion
bool Shifter::Find_Solution(int index)
{
	bool checkshape;
	bool checksol;
	bool ones;

	// Looping through the grid
	for (unsigned int i = 0; i < Grid.size(); i++)
	{
		for (unsigned int j = 0; j < Grid[i].size(); j++)
		{
			// Applying the shape at each spot in the grid
			checkshape = Apply_Shape(index, i, j);

			// Executes if there are more shapes to check
			if ((checkshape == true) && (index != (int) Shapes.size()-1))
			{
				// Calls itself with the next shape
				checksol = Find_Solution(index + 1);			

				/* If both shapes solve the puzzle, adds the row and 
				   column to the solution vector and returns true */
				if (checksol == true)
				{
					Solution_Rows.push_back(i);
					Solution_Cols.push_back(j);
					return true;
				}
			}

			// Executes once we try all shapes and all possible positions
			else if ((checkshape == true) && (index == (int) Shapes.size()-1))
			{
				/* The ones variable is what I use to see if the 
				   puzzle was solved (if the grid contains all 1's) */
				ones = true;

				// Checks to see if there are any 0's in the grid
				for (unsigned int a = 0; a < Grid.size(); a++)
					for (unsigned int b = 0; b < Grid[a].size(); b++)
						if (Grid[a][b] == '0')
							ones = false;
	
				// If the grid contains all 1's we add the solution
				if (ones == true)
				{
					Solution_Rows.push_back(i);
					Solution_Cols.push_back(j);
					return true;
				}
			}

			// Reverting the changes made if the shape doesn't fit
			Apply_Shape(index, i, j);
		}
	}

	// If we reach this point, there was no solution
	return false;
}

// This function will print the shapes and their solutions
void Shifter::Print_Solution() const
{
	vector <string> s;

	// Looping through all of the shapes
	for (unsigned int i = 0; i < Shapes.size(); i++)
	{
		/* Once again, I'm using a temporary vector 
		   that way I'm working in 2d rather than 3d */
		s = Shapes[i];

		// Printing out the shape
		for (unsigned int j = 0; j < s.size(); j++)
		{
			for (unsigned int k = 0; k < s[j].size(); k++)
				cout << s[j][k];
			cout << " ";
		}

		/* Printing out the solution to the shape. I loop through the vectors
		   backwards because the solution for the last shape in Shapes is 
		   stored before its predecessors. */
		cout << Solution_Rows[Solution_Rows.size()-1-i] << " "
			 << Solution_Cols[Solution_Cols.size()-1-i] << '\n';
	} 
}
