#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int getClosestSum(vector<int> &elements, int query)
{
    int minimumDifference = numeric_limits<int>::max();
    int closestSum = 0;
    for (auto value1 = elements.begin(); value1 + 1 != elements.end(); ++value1)
    {
        for (auto value2 = value1 + 1; value2 != elements.end(); ++value2)
        {
            int sum = *value1 + *value2;
            int difference = abs(sum - query);
            if (difference < minimumDifference)
            {
                minimumDifference = difference;
                closestSum = sum;
            }
        }
    }
    return closestSum;
}

int main()
{
    int numElements;  // 1 < n ≤ 1000
    int oneBasedIndex = 0;
    cin >> numElements;
    while (numElements != 0)
    {
        ++oneBasedIndex;
        cout << "Case " << oneBasedIndex << ":" << endl;

        vector<int> v1(numElements);
        for (int i = 0; i < numElements; ++i)
        {
            cin >> v1.at(i);
        }
        int numQueries;  // 0 < m < 25
        cin >> numQueries;
        for (int i = 0; i < numQueries; ++i)
        {
            int query;
            cin >> query;
            int sum = getClosestSum(v1, query);
            cout << "Closest sum to " << query << " is " << sum << "." << endl;
        }
        cin >> numElements;
    }
    return 0;
}
