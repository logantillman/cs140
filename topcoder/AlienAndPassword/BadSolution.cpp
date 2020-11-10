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

class AlienAndPassword {
  public:
    int getNumber(string S);
};

/* find() is a procedure that finds string s in vector v.
   If s is in v, find() returns the index of s.
   Otherwise, it returns -1 */

int find(vector <string> v, string s)
{
  int i;

  for (i = 0; i < v.size(); i++) if (v[i] == s) return i;
  return -1;
}

/* Solve the problem by creating each potential password,
   and then trying to find it in a list of potential
   passwords.  If it's not there, add it to the list, and
   then return the list's size. */

int AlienAndPassword::getNumber(string S)
{
  vector <string> pot;
  string p;
  int i;

  for (i = 0; i < S.size(); i++) {
    p = S.substr(0,i) + S.substr(i+1);
    if (find(pot, p) == -1) pot.push_back(p);
  }
  return pot.size();
}
