// moonglow.cpp
// CS 140
// Logan Tillman
// 08-29-19
// This program reads through text and pulls out a name
// and calculates a test score for based on the input

#include <iostream>
using namespace std;

int main()
{
	string input, name;
	double num;
	double score = 0;

		while (true)
		{
			// Running total for the score of the non-average numbers
			while (cin >> num)
				score += num;
	
			// Puts the word into a variable for comparison if not a number
			if (!(cin >> num))
			{
				cin.clear();
				cin >> input;
			}
		
			// Checks to see if its reading in the name
			if (input == "NAME")
				cin >> name;

			// Checks to see if its going to average numbers
			else if (input == "AVERAGE")
			{
				int i = 0;
				double temp = 0;

				while (cin >> num)
				{
					temp += num;
					++i;
				}

				// Check to keep the output from resulting in NaN
				if (temp != 0)
				{
					temp /= i;
					score += temp;
				}
			}
	
			// Breaks from the loop once it reaches the end
			if (cin.eof())
				break;	
		}

		cout << name << " " << score << '\n';

	return 0;
}
