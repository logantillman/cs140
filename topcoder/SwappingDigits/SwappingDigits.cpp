#include <vector>
#include <string>
#include <iostream>
using namespace std;

class SwappingDigits {
  public:
    string minNumber(string num);
};

string SwappingDigits::minNumber(string num) 
{
	vector <int> characters;

	characters.resize(10, -1);

	for (int i = 0; i < num.size(); i++)
	{
		int val;

		val = num[i] - '0';

		characters[val] = i;
	}

	for (int i = 0; i < num.size(); i++)
	{
		
	}

  return "";
}
