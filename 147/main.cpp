#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

const int denominations[] = {10000, 5000, 2000, 1000, 500, 200, 100, 50, 20, 10, 5};// in cents
const int numDenominations = sizeof(denominations) / sizeof(denominations[0]);
const int MAX_AMOUNT = 30000;
long long table[numDenominations + 1][MAX_AMOUNT + 1];

void fillTable()
{
    for (int i = 0; i <= numDenominations; ++i)
    {
        table[i][0] = 1;
    }
    for (int j = 1; j <= MAX_AMOUNT; ++j)
    {
        table[0][j] = 0;
    }
    for (int i = 1; i <= numDenominations; ++i)
    {
        for (int j = 1; j <= MAX_AMOUNT; ++j)
        {
            long long excluded = table[i - 1][j];
            int denomination = denominations[i - 1];
            long long included = (j >= denomination) ? table[i][j - denomination] : 0;
            table[i][j] = excluded + included;
        }
    }
}

void outputLine(int amount)
{
    cout << right << setw(6) << fixed << setprecision(2) << amount / 100.0
         << right << setw(17) << table[numDenominations][amount] << endl;
}

int main()
{
    fillTable();
    string input;
    while (cin >> input, input != "0.00")
    {
        int amount = (int) lround(100 * stod(input));
        outputLine(amount);
    }
    return 0;
}
