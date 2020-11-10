// enum.cpp
// Lab 9
// CS 140
// Author: Logan Tillman
// Date: November 13, 2019

/* This program will enumerate all strings of the given length and number 
   of ones. The rest of the string's length will be filled with zeros */

#include <iostream>
#include <sstream>
using namespace std;

// This function recursively calls itself to do the enumeration
void do_enumeration(string &s, int index, int n_ones)
{
	// Prints out the enumerated string
	if (index == (int) s.size() && n_ones == 0)
	{
		cout << s << '\n';
		return;
	}

	// Executes when the enumeration isn't valid
	else if (index == (int) s.size() && n_ones != 0)
		return;

	else
	{
		// Adds 0's until we have to add 1's
		if (index < ((int) s.size() - n_ones))
		{
			s[index] = '0';
			
			// Calls itself with the next index
			do_enumeration(s, index+1, n_ones);
		}

		// Adds 1's until it can't
		if (n_ones > 0)
		{
			s[index] = '1';

			/* Calls itself with the next index and 
			   decrements the number of ones left. */
			do_enumeration(s, index+1, n_ones-1);
		}
	}
}

int main (int argc, char **argv)
{
	// Checks to make sure enough arguments are entered
	if (argc != 3)
		return 1;
	
	stringstream ss;
	string s;
	int size;
	int n_ones;

	// Converting the variables to integers and resizing the string
	ss.str(argv[1]);
	ss >> size;
	ss.clear();
	ss.str(argv[2]);
	ss >> n_ones;
	s.resize(size);

	// Calling the enumeration function on the string
	do_enumeration(s, 0, n_ones);	

	return 0;
}
