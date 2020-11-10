#include <string>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main(int argc, char **argv)
{
  int ws, ss, i, as;
  char buf[500];
  ifstream fin;
  string s;
  set <string> all;
  vector <string> w;
  vector <string> sp;
  vector <string> r;

  if (argc != 4) printf("usage a.out words-size speech-size all-size\n");
  ws = atoi(argv[1]);
  ss = atoi(argv[2]);
  as = atoi(argv[3]);

  sprintf(buf, "random_names %d > junk.txt", as*2);
  system(buf);
  srand48(time(0));

  fin.open("junk.txt");
  while ((fin >> s) && all.size() < as) {
    for (i = 0; i < s.size(); i++) if (s[i] >= 'A' && s[i] <= 'Z') s[i] += ('a'-'A');
    if (all.find(s) == all.end()) {
      if (w.size() < ws) w.push_back(s);
      r.push_back(s);
      all.insert(s);
    }
  }

  for (i = 0; i < ss; i++) {
    sp.push_back(r[drand48()*as]);
  }

  printf("( echo");
  for (i = 0; i < w.size(); i++) printf(" %s", w[i].c_str());
  printf(" ; echo");
  for (i = 0; i < sp.size(); i++) printf(" %s", sp[i].c_str()); printf("\n");
  printf(" ) | ./a.out -\n");
  
  return 0;
}
