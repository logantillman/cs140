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

int main()
{
  int iter, i;
  int size;
  string init;

  for (iter = 0; iter < 100; iter++) {
    init.clear(); 
    if (iter < 20) {
      size = (drand48() * 10) + 1;
    } else if (iter < 40) {
      size = (drand48() * 100) + 1;
    } else if (iter < 60) {
      size = (drand48() * 1000) + 1;
    } else if (iter < 80) {
      size = (drand48() * 10000) + 1;
    } else {
      size = (drand48() * 100000) + 1;
    }
    for (i = 0; i < size; i++) init.push_back('a' + (int) (drand48() * 24));
    printf("%s\n", init.c_str());
  }
  return 0;
}
