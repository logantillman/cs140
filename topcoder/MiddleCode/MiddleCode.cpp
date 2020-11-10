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

class MiddleCode {
  public:
    string encode(string s);
};

string MiddleCode::encode(string s)
{
	string t;
	int size = s.size();
	for (int i = 0; i < size; i++)
	{
		if ((s.size() % 2) == 0)
		{
			char a, b;
			a = s.size()/2;
			b = s.size()/2 + 1;
			if (s[a] > s[b])
				t.append(b);
			else if (s[a] <= s[b])
				t.append(a);
		}	
		else if ((s.size() % 2) != 0)
		{
			
		}
	}
  return "";
}
