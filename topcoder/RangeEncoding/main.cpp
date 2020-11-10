#include "RangeEncoding.cpp"

int main(int argc, char **argv)
{
  int i, num, j;
  class RangeEncoding TheClass;
  int retval;
  vector <int> arr;

  if (argc != 2) { fprintf(stderr, "usage: a.out num\n"); 
                   fprintf(stderr, "numbers 0 through 5 correspond to the topcoder examples.\n");
                   fprintf(stderr, "numbers between 5 and 1000000 generate a random input with\n");
                   fprintf(stderr, "that many elements in the vector.\n");
                   exit(1); }

 if (atoi(argv[1]) == 0) {
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(7);
    arr.push_back(8);
    arr.push_back(9);
    arr.push_back(10);
  }

 if (atoi(argv[1]) == 1) {
    arr.push_back(1);
    arr.push_back(6);
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(32);
    arr.push_back(49);
  }

 if (atoi(argv[1]) == 2) {
    arr.push_back(2);
    arr.push_back(4);
    arr.push_back(5);
    arr.push_back(6);
    arr.push_back(8);
    arr.push_back(9);
    arr.push_back(10);
    arr.push_back(11);
    arr.push_back(12);
    arr.push_back(15);
  }

 if (atoi(argv[1]) == 3) {
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(7);
    arr.push_back(11);
    arr.push_back(13);
    arr.push_back(17);
    arr.push_back(19);
    arr.push_back(23);
    arr.push_back(29);
    arr.push_back(31);
    arr.push_back(37);
    arr.push_back(41);
    arr.push_back(43);
    arr.push_back(47);
  }

 if (atoi(argv[1]) == 4) {
    arr.push_back(10);
    arr.push_back(11);
    arr.push_back(12);
    arr.push_back(13);
    arr.push_back(14);
    arr.push_back(15);
    arr.push_back(20);
    arr.push_back(21);
    arr.push_back(22);
    arr.push_back(23);
    arr.push_back(25);
    arr.push_back(27);
    arr.push_back(28);
    arr.push_back(29);
    arr.push_back(30);
    arr.push_back(31);
    arr.push_back(32);
    arr.push_back(33);
  }

 if (atoi(argv[1]) == 5) {
    arr.push_back(33);
  }

  num = atoi(argv[1]);
  if (num > 5 && num <= 1000000) {
    j = 1;
    srand48(num);
    for (i = 0; i < num; i++) {
      while (drand48() < .5) j++;
      arr.push_back(j);
      j++;
    }
  }
      
  retval = TheClass.minRanges(arr);
  cout << retval << endl;

  exit(0);
}
