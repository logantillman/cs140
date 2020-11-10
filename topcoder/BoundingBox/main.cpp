#include "BoundingBox.cpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
  string arg;
  vector <int> x, y;
  BoundingBox b;
  int i;
  size_t j;

  if (argc != 2) {
    cerr << "usage: a.out example-number-or-dash\n";
    return 1;
  }

  arg = argv[1];
  if (arg == "-") {
    while (cin >> i) x.push_back(i);
    if (x.size() == 0 || x.size() % 2 == 1) {
      cerr << "Bad input -- needs to be a positive and even number of integers.\n";
      return 1;
    }
    for (j = x.size() / 2; j < x.size(); j++) y.push_back(x[j]);
    x.resize(x.size() / 2);
  } else if (atoi(argv[1]) == 0) {
    x.push_back(0);
    x.push_back(1);
    y.push_back(1);
    y.push_back(0);
  } else if (atoi(argv[1]) == 1) {
    x.push_back(0);
    x.push_back(-2);
    x.push_back(-1);
    y.push_back(-1);
    y.push_back(-1);
    y.push_back(-2);
  } else if (atoi(argv[1]) == 2) {
    x.push_back(0);
    x.push_back(0);
    x.push_back(1);
    x.push_back(0);
    x.push_back(-1);
    x.push_back(2);

    y.push_back(0);
    y.push_back(1);
    y.push_back(2);
    y.push_back(-2);
    y.push_back(0);
    y.push_back(-1);
  } else if (atoi(argv[1]) == 3) {

    x.push_back(9);
    x.push_back(-88);
    x.push_back(-40);
    x.push_back(98);
    x.push_back(-55);
    x.push_back(41);
    x.push_back(-38);

    y.push_back(-65);
    y.push_back(56);
    y.push_back(-67);
    y.push_back(7);
    y.push_back(-58);
    y.push_back(33);
    y.push_back(68);
  } else {
    cerr << "Bad example number.\n";
    return 1;
  }
  cout << b.smallestArea(x, y) << endl;
  return 0;
}

