#include <iostream>

using namespace std;

const int denominations[] = {1, 5, 10, 25, 50};
const int numDenominations = sizeof(denominations) / sizeof(denominations[0]);
const int amount = 30000;
long long table[numDenominations + 1][amount + 1];

void fillTable()
{
    for (int i = 0; i <= numDenominations; ++i)
    {
        table[i][0] = 1;
    }

    for (int j = 0; j <= amount; ++j)
    {
        table[0][j] = 0;
    }

    for (int i = 1; i <= numDenominations; ++i)
    {
        for (int j = 1; j <= amount; ++j)
        {
            long long excluded = table[i - 1][j];
            int denomination = denominations[i - 1];
            if (denomination <= j)
            {
                long long included = table[i][j - denomination];
                table[i][j] = included + excluded;
            }
            else
            {
                table[i][j] = excluded;
            }
        }
    }
}

void outputLine(int n)
{
    long long m = table[numDenominations][n];
    if (m == 1)
    {
        cout << "There is only 1 way to produce " << n << " cents change." << endl;
    }
    else
    {
        cout << "There are " << m << " ways to produce " << n << " cents change." << endl;
    }
}

int main()
{
    fillTable();
    int n; // between 0 and 30000 inclusive
    while (cin >> n)
    {
        outputLine(n);
    }
    return 0;
}
