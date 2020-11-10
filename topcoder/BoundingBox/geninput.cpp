#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
  int num;
  int j;

  srand48(time(0));

  if (cin >> num) {
    cout << "echo";
    while (num > 0) {
      j = 1000 - drand48() * 2000;
      cout << " " << j;
      j = 1000 - drand48() * 2000;
      cout << " " << j;
      num--;
    }
    cout << " | ./a.out\n";
  }
  return 0;
}
