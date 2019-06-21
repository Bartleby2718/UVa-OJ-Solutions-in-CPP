#include <iostream>
#include <set>

using namespace std;

int main()
{
    int numDays; // 1 ≤ n ≤ 5000
    cin >> numDays;
    while (numDays != 0)
    {
        multiset<long> billAmounts; // The total number of all bills is no bigger than 10^6
        long sum = 0;
        for (int i = 0; i < numDays; ++i)
        {
            long numBills; // 0 ≤ k ≤ 10^5
            cin >> numBills;
            for (long j = 0; j < numBills; ++j)
            {
                long billAmount; // positive integers less than 10^6
                cin >> billAmount;
                billAmounts.insert(billAmount);
            }
            // These are distinct because at the end of each day there are at least two bills in the urn
            auto smallestIt = billAmounts.begin();
            long smallest = *smallestIt;
            billAmounts.erase(smallestIt);
            auto biggestIt = --billAmounts.end();
            long biggest = *biggestIt;
            long difference = biggest - smallest;
            billAmounts.erase(biggestIt);
            sum += difference;
        }
        cout << sum << endl;
        cin >> numDays;
    }
    return 0;
}
