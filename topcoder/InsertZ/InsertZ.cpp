#include <cstring>
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

class InsertZ {
  public:
    string canTransform(string init, string goal);
};

string InsertZ::canTransform(string init, string goal)
{
	string temp;
	for (int i = 0; i < goal.size(); i++)
	{
		if (goal[i] != 'z')
			temp += goal[i];
	}

	if (init == temp)
		return "Yes";
	else if (init != temp)
		return "No";

  return "";
}
