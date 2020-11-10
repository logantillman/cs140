#include "CatchTheBeatEasy.cpp"

#include <vector>
#include <string>
#include <sstream>

int main(int argc, char **argv)
{
  int i;
  class CatchTheBeatEasy TheClass;
  string retval;
  vector <int> x;
  vector <int> y;
  string s, line;
  istringstream ss;

  if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); exit(1); }

  s = argv[1];
  if (s == "-") {
   if (!getline(cin, line)) return 0;
   ss.str(line);
   while (ss >> i) x.push_back(i);
   if (!getline(cin, line)) return 0;
   ss.clear();
   ss.str(line);
   while (ss >> i) y.push_back(i);
  } else {

 
/*
  x = ;
  y = ;
*/


 if (atoi(argv[1]) == 0) {
    x.push_back(-1);
    x.push_back( 1);
    x.push_back( 0);
    y.push_back(1);
    y.push_back( 3);
    y.push_back( 4);
  }

 if (atoi(argv[1]) == 1) {
    x.push_back(-3);
    y.push_back(2);
  }

 if (atoi(argv[1]) == 2) {
    x.push_back(-1);
    x.push_back( 1);
    x.push_back( 0);
    y.push_back(1);
    y.push_back( 2);
    y.push_back( 4);
  }

 if (atoi(argv[1]) == 3) {
    x.push_back(0);
    x.push_back( -1);
    x.push_back( 1);
    y.push_back(9);
    y.push_back( 1);
    y.push_back( 3);
  }

 if (atoi(argv[1]) == 4) {
    x.push_back(70);
    x.push_back(-108);
    x.push_back(52);
    x.push_back(-70);
    x.push_back(84);
    x.push_back(-29);
    x.push_back(66);
    x.push_back(-33);
    y.push_back(141);
    y.push_back(299);
    y.push_back(402);
    y.push_back(280);
    y.push_back(28);
    y.push_back(363);
    y.push_back(427);
    y.push_back(232);
  }

 if (atoi(argv[1]) == 5) {
    x.push_back(-175);
    x.push_back(-28);
    x.push_back(-207);
    x.push_back(-29);
    x.push_back(-43);
    x.push_back(-183);
    x.push_back(-175);
    x.push_back(-112);
    x.push_back(-183);
    x.push_back(-31);
    x.push_back(-25);
    x.push_back(-66);
    x.push_back(-114);
    x.push_back(-116);
    x.push_back(-66);
    y.push_back(320);
    y.push_back(107);
    y.push_back(379);
    y.push_back(72);
    y.push_back(126);
    y.push_back(445);
    y.push_back(318);
    y.push_back(255);
    y.push_back(445);
    y.push_back(62);
    y.push_back(52);
    y.push_back(184);
    y.push_back(247);
    y.push_back(245);
    y.push_back(185);
  }

 if (atoi(argv[1]) == 6) {
    x.push_back(0);
    x.push_back(0);
    x.push_back(0);
    x.push_back(0);
    y.push_back(0);
    y.push_back(0);
    y.push_back(0);
    y.push_back(0);
  }
  }

  retval = TheClass.ableToCatchAll(x, y);
  cout << retval << endl;

  exit(0);
}
