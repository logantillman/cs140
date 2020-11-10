#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class CatchTheBeatEasy {
  public:
    string ableToCatchAll(vector <int> x, vector <int> y);
};

string CatchTheBeatEasy::ableToCatchAll(vector <int> x, vector <int> y)
{
	map <int, int> candies;
	map <int, int>::const_iterator cit;
	int cx, cy;
	int diffx, diffy;

	cx = 0;
	cy = 0;

	for (int i = 0; i < x.size(); i++)
		candies[y[i]] = x[i];

	for (cit = candies.begin(); cit != candies.end(); cit++)
	{
		diffx = cit->second - cx;
		diffy = cit->first - cy;

		if (diffx < 0)
			diffx *= -1;

		if (diffy < 0)
			diffy *= -1;

		if (diffy >= diffx)
		{
			cy = cit->first;
			cx = cit->second;
		}
		else
			return "Not able to catch";

//		if ((cit->first - cy) < (cit->second - cx))
//			return "Not able to catch";
//		else
//		{
//			cy = cit->first;
//			cx = cit->second;
//		}
	}

	return "Able to catch";
}
