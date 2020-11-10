#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class TreesAndBrackets {
  public:
    string check(string t1, string t2);
};

string TreesAndBrackets::check(string t1, string t2)
{
	int i;
	vector <int> m1, m2;

	m1.resize(t1);
	m2.resize(t2);

	for (i = 0; i < t1.size(); i++)
	{	
		if (t1[i] == '(')
			m1.push_back(i);
		if (t1[i] == ')')

	}	

	
  return "";
}
