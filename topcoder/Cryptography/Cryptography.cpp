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

class Cryptography {
  public:
    long long encrypt(vector <int> numbers);
};

long long Cryptography::encrypt(vector <int> numbers)
{
	int min = 1001;
	int position;
	long long prod = 1;

	for (int i = 0; i < numbers.size(); i++)
	{
		if (numbers[i] < min)
			min = numbers[i];
			position = i;
	}

	numbers[position]++;

	for (int i = 0; i < numbers.size(); i++)
		prod = prod * numbers[i];	

  return prod;
}

