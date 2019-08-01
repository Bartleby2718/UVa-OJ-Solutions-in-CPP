#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/
long getMinimalDifference(const vector<int>& values)
{
    int numCoins = values.size();
    long sum = 0;
    for (int value:values)
    {
        sum += value;
    }

    bool included[numCoins + 1][sum + 1];
    for (int i = 0; i <= numCoins; ++i)
    {
        included[i][0] = true;
    }

    for (long j = 1; j <= sum; ++j)
    {
        included[0][j] = false;
    }

    for (int i = 1; i <= numCoins; ++i)
    {
        for (long j = 1; j <= sum; ++j)
        {
            included[i][j] = included[i - 1][j];
            int nextValue = values.at(i - 1);
            if (nextValue <= j)
            {
                included[i][j] |= included[i - 1][j - nextValue];
            }
        }
    }

    long difference = numeric_limits<long>::max();
    for (long j = sum / 2; j >= 0; --j)
    {
        if (included[numCoins][j])
        {
            difference = sum - 2 * j;
            break;
        }
    }
    return difference;
}

int main()
{
    int numProblems;
    cin >> numProblems;
    for (int i = 0; i < numProblems; ++i)
    {
        int numCoins; // non-negative integer m ≤ 100
        cin >> numCoins;
        vector<int> values;
        for (int j = 0; j < numCoins; ++j)
        {
            int value; // from 1 cent to 500 cents
            cin >> value;
            values.push_back(value);
        }
        long difference = getMinimalDifference(values);
        cout << difference << endl;
    }
    return 0;
}
