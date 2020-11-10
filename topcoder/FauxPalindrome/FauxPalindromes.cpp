#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class FauxPalindromes {
  public:
    string classifyIt(string word);
};

bool is_it_p(string s)
{
	for (int i = 0; i < s.size() / 2; i++)
	{
		if(s[i] != s[s.size()-i-1])
			return false;
		return true;
	}
}

string FauxPalindromes::classifyIt(string w)
{

	if (is_it_p(w))
		return "PALINDROME";

	char c = '\0';
	string faux;
	for (int i = 0; i < w.size(); i++)
	{
		if(w[i] != c)
		{
			faux.push_back(w[i]);
			c = w[i];
		}
	}

	if (is_it_p(faux))
		return "FAUX";
	else
		return "NOT EVEN FAUX";

  return "yerrr";
}
