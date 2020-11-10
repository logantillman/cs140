#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
	char item;
	int count;

	while (cin >> item)
	{
		switch(item)
		{
			case('.'):
				break;
			case('-'):
				break;
			default:
				count += item - 64;
				break;
		}
	}

	cout << count << '\n';
return 0;
}

