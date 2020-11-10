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

class DistanceBetweenStrings {
  public:
    int getDistance(string a, string b, string letterSet);
};

int DistanceBetweenStrings::getDistance(string a, string b, string l)
{
	int total = 0;
	int numa = 0;
	int numb = 0;

	for (int i = 0; i < l.size(); i++)
	{
		numa = 0;
		numb = 0;
		for (int j = 0; j < a.size(); j++)
			if (a[j] == l[i])
				++numa;
		for (int k = 0; k < b.size(); k++)
			if (b[k] == l[i])
				++numb;
		total += ((numa - numb) * (numa - numb));
	}

  return total;
}
