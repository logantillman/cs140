#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
using namespace std;

int main()
{
	string key;
    stringstream ss;
    string tempkey;
    vector <string> strings;
    vector <int> hexcheck;
    string rv;
    int count = 0;
    int total = 0;

	cout << "Input key: ";
	cin >> key;

    for (int i = 0; i < key.size(); i++)
    {
        tempkey = tempkey + key[i];
        ++count;

        if ((count == 7) || (i == (key.size()-1)))
        {
//			cout << "Strings[" << i << "] = " << tempkey << '\n';
            strings.push_back(tempkey);
            tempkey = "";
            count = 0;
        }

    }

//	cout << "Strings.size() = " << strings.size() << '\n';
	hexcheck.resize(strings.size());

    for (int i = 0; i < strings.size(); i++)
    {
		stringstream s;
//		cout << "Really.. string[i] = " << strings[i] << '\n';
        s << strings[i];
        s.clear();
        if(!(s >> hex >> hexcheck[i]))
		{
			cout << "Error\n";
            return 1;
		}
    }

    for (int i = 0; i < hexcheck.size(); i++)
    {
//		printf ("0x%x\n", hexcheck[i]);
        total = total ^ hexcheck[i];
    }

    ss << hex << total;
    ss >> rv;

    cout << "RV = " << rv << '\n';

return 0;
}
