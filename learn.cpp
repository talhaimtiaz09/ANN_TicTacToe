#include <iostream>
using namespace std;
int main()
{
    int c1, c2;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cout << i / 3 + j << endl;
    return 0;
}