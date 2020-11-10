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

class FoxAndWord {
  public:
    int howManyPairs(vector <string> words);
};

int FoxAndWord::howManyPairs(vector <string> words)
{
/*	for (int i = 0; i < words.size(); i++)
	{
		for (int j = 0; j < words[i].size(); j++)
		{
			string s2 = words[i].substr(0, j);
			string s3 = words[i].substr(j, words[i].size()-j);
			
			for (int k = 0; k < words.size(); k++)
			{
				if ((s3+s2) == words[k])
					return 1;
			}

		}
	}	*/

	int count = 0;

		
  return 0;
}
