#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
  int i, t, l, h, b;

  srand48(time(0));
  b = drand48() * 8 + 1;
  
  cin >> t;

  // printf("%d\n", t);

  printf("echo");
  for (i = 0; i < t; i++) {
    l = (int) (drand48()*10+16);
    h = drand48()*3;
    h -= 1;
    printf(" %d", (b << l) + h);
  }
  printf(" | ./a.out -\n");
  return 0;
}
