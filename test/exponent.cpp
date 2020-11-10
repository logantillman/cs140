#include <iostream>
#include <cstdio>
using namespace std;

int main(int argc, char** argv)
{
	int num, exp;
	int total;
	printf("Enter 'num exp': ");
	cin >> num >> exp;

	total = num;

	for (int i = 1; i < exp; i++)
		total *= num;

	printf("Answer of %d^%d = %d\n", num, exp, total);

	return 0;
}
