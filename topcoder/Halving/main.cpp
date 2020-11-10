#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include "Halving.cpp"

int main(int argc, char **argv)
{
  int i;
  class Halving TheClass;
  int retval;
  vector <int> a;
  string av;

  if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }
  av = argv[1];
  if (av == "-") {
    while (cin >> i) a.push_back(i);
  } else {

/*
  a = ;
*/


 if (atoi(argv[1]) == 0) {
    a.push_back(11);
    a.push_back(4);
  }

 if (atoi(argv[1]) == 1) {
    a.push_back(1000000000);
    a.push_back(1000000000);
    a.push_back(1000000000);
    a.push_back(1000000000);
  }

 if (atoi(argv[1]) == 2) {
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);
    a.push_back(6);
    a.push_back(7);
  }

 if (atoi(argv[1]) == 3) {
    a.push_back(13);
    a.push_back(13);
    a.push_back(7);
    a.push_back(11);
    a.push_back(13);
    a.push_back(11);
  }

 if (atoi(argv[1]) == 4) {
    a.push_back(1);
    a.push_back(1);
  }
  }

  retval = TheClass.minSteps(a);
  cout << retval << endl;

  exit(0);
}
