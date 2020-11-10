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

typedef vector <int> IVec;

class Halving {
  public:
    int minSteps(vector <int> a);
};

void all_breaks(int len, int breaks, map <int, int> &m)
{
	map <int, int>::const_iterator mit;

	mit = m.find(len);

	if (mit != m.end())
	{
		if (mit->second <= breaks)
			return;
	}

	m[len] += breaks;

	if (len > 1)
	{
		int odd = len % 2;

		if (odd > 0)
			all_breaks((len/2)+1, breaks + 1, m);

		all_breaks((len/2), breaks + 1, m);
	}
}

int Halving::minSteps(vector <int> a)
{
  map <int, int> m;
  map <int, int> canbreak, minbreaks;
  map <int, int>::iterator mit;
  int minval;
  size_t i;

  for (unsigned int i = 0; i < a.size(); i++)
  {
	all_breaks(a[i], 0, m);
  }

	for (unsigned int i = 0; i < a.size(); i++)
	{
		canbreak[a[i]] = 1;
		minbreaks[a[i]] = 0;
	}

  for (mit = m.begin(); mit != m.end(); mit++)
	{
		cout << mit->first << " " << mit->second << '\n';
		canbreak[mit->first] += 1;
		minbreaks[mit->first] += mit->second;
	}

/*  minval = 100000000;

  for (mit = minbreaks.begin(); mit != minbreaks.end(); mit++)
  {
	if (mit->second >= a.size())
		if (minval > mit->second)
			minval = mit->second;
  }	
*/
}
