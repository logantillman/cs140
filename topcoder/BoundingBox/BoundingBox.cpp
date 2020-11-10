#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

class BoundingBox {
  public:
    int smallestArea(const vector <int> &X, const vector <int> &Y);
};

int MinMax (const vector <int> &num);

int BoundingBox::smallestArea(const vector <int> &X, const vector <int> &Y)
{
	int diffx;
	int diffy;

	diffx = MinMax(X);
	diffy = MinMax(Y);

  return diffx * diffy;
}

int MinMax (const vector <int> &num)
{
    int min;
    int max;

    min = num[0];
    max = num[0];

    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] > max)
            max = num[i];
        if (num[i] < min)
            min = num[i];
    }
    return max-min;
}
