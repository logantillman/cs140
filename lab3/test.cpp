#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

vector <int> vflip (vector <int> pixels, int rows, int columns, int col);

int main()
{
	vector<int> pixels; // = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int num;
	int columns = 4;
	int rows = 4;

/*	for (int i = 0; i < 16; i++)
	{
		pixels.push_back(i);
	}		
*/

	while (cin >> num)
		pixels.push_back(num);

	for (int i = 0; i < pixels.size(); i++)
    {
        cout << pixels[i] << " ";
    }
		cout << '\n';
//	for (int col = 0; col < columns; col++)
//	{
		pixels = vflip (pixels, rows, columns, 0);
//	}

	for (int i = 0; i < pixels.size(); i++)
	{
		cout << pixels[i] << " ";
	}

	return 0;
}

vector <int> vflip (vector <int> pixels, int rows, int columns, int col)
{
    int temp;

    for (int i = 0; i < (rows/2); i++)
    {
//        int a = pixels[(columns * i) + col];
		int a = ((columns*i) + col);
		cout << "a = " << a << " i = " << i; //<< " col = " << col << " i = " << i;
 //       int b = pixels[(((rows * columns) - columns) + col) - (i * columns)];
		int b = ((((rows*columns)-columns)+col)-(i*columns));
		cout << " b = " << b << " i = " << i <<'\n';  //<< " col = " << col << " i = " << i;
        temp = pixels[a];
//		cout << " temp (a) = " << temp;
        pixels[a] = pixels[b];
//		cout << " pixels[a] (b) = " << pixels[a];
        pixels[b] = temp;
//		cout << " pixels[b] (a) = " << pixels[b] << '\n';

		for (int i = 0; i < pixels.size(); i++)
    {
        cout << pixels[i] << " ";
    }
        cout << '\n';		
		
	}
	return pixels;
}
