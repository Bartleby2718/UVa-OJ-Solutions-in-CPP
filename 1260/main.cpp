#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int numTestCases;
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; ++i)
    {
        int listSize;  // 2 ≤ n ≤ 1000
        cin >> listSize;
        vector<int> v1(listSize);  //  1 ≤ a_i ≤ 5000
        for (int j = 0; j < listSize; ++j)
        {
            cin >> v1.at(j);
        }
        long total = 0;
        for (int j = 1; j < listSize; ++j)
        {
            long count = 0;
            int todaySalesAmount = v1[j];
            for (int k = 0; k < j; ++k)
            {
                int previousSalesAmount = v1[k];
                if (previousSalesAmount <= todaySalesAmount)
                {
                    ++count;
                }
            }
            total += count;
        }
        cout << total << endl;
    }
    return 0;
}
