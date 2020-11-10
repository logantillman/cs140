#include <string>
#include <deque>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

string grs(int maxl, int maxs)
{
  int l, s, i, j;
  string rv;

  if (maxl == 0) return "";
  s = (drand48() * maxs) + 1;  

  rv += "(";
  for (i = 0; i < s; i++) {
    l = (drand48() * maxl);  
    rv += grs(l, maxs);
  }
  rv += ")";
  return rv;
}

string add_to(const string &s, int sindex, double addperc, double skipperc, const vector <int> &M1)
{
  string rv;
  int a;

  rv = "(";

  a = sindex+1;
  while (1) {
    if (drand48() < addperc) rv += grs(drand48()*5, drand48()*5);
    if (a == M1[sindex]) { rv += ")"; return rv; }
    if (drand48() < skipperc) {
    } else {
      rv += add_to(s, a, addperc, skipperc, M1);
    }
    a = M1[a]+1;
  }
}

int main()
{
  int maxl, maxs, i;
  vector <int> M1;
  deque <int> s;
  string t2, t1;
  double skipperc, addperc;

  srand48(time(0));

  cin >> maxl >> maxs >> addperc >> skipperc;

  t2 = grs(maxl, maxs);

  M1.resize(t2.size(), -1);
  for (i = 0; i < t2.size(); i++) {
    if (t2[i] == '(') {
      s.push_front(i);
    } else {
      M1[i] = s[0];
      M1[s[0]] = i;
      s.pop_front();
    }
  }

  t1 = add_to(t2, 0, addperc, skipperc, M1);

  cout << t1 << " " << t2 << endl;

  return 0;
}
