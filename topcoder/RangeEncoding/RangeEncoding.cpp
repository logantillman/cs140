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

class RangeEncoding {
  public:
    int minRanges(vector <int> arr);
};

int RangeEncoding::minRanges(vector <int> arr)
{
  int i = 1;

	for (int j = 1; j < arr.size(); j++)
	{
		if (arr[j] == (arr[j-1]+1))
			continue;
		++i;
	}

  return i;
}
