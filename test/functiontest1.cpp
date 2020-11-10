#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

int main()
{
	string key;
    string tempkey;
    stringstream ss;
    int hexcheck;
	int index;
	
	cin >> key;

    if (key.size() > 7)
        for (int i = 1; i <= 7; i++)
            tempkey = key[key.size()-i] + tempkey;
	else
		tempkey = key;

    ss << tempkey;
    ss.clear();
    if(!(ss >> hex >> hexcheck))
	{
        cout << "Error";
		return 1;
	}
    cout << tempkey << '\n';
	
	ss.clear();
	ss << tempkey;
    ss >> hex >> index;
//    index = index % Vals.size();
	cout << index << '\n';

return 0;
}
