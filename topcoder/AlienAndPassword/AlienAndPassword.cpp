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

class AlienAndPassword {
  public:
    int getNumber(string S);
};

int AlienAndPassword::getNumber(string S)
{
	string o;
	for(int i = 1; i < S.size(); i++)
	{
		if (S[i] != S[i-1])
		{
			o += S[i];
		}
	}
  return 0;
}
