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

class LongLiveZhangzj {
  public:
    int donate(vector <string> speech, vector <string> words);
};

int LongLiveZhangzj::donate(vector <string> speech, vector <string> words)
{
	set <string> wset;
	int rv;

	rv = 0;

	for (int i = 0; i < words.size(); i++)
		wset.insert(words[i]);

	for (int i = 0; i < speech.size(); i++)
		if (wset.find(speech[i]) != wset.end())
			rv++;

   return rv;
}
