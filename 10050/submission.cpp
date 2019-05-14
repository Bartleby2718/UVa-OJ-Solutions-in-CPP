#include <iostream>
#include <vector>

using namespace std;

int getNumWorkingDaysLost(int numDays, vector<int> &periods)
{
    int numDaysLost = 0;
    for (int day = 1; day <= numDays; ++day)
    {
        /* no hartals on weekly holidays (on Fridays and Saturdays).*/
        if (day % 7 == 6 || day % 7 == 0)
        {
            continue;
        }
        /* check for each party */
        for (int period : periods)
        {
            if (day % period == 0)
            {
                ++numDaysLost;
                break;
            }
        }
    }
    return numDaysLost;
}

void testGetNumWorkingDaysLost(int numDays, vector<int> &periods, int expected)
{
    int actual = getNumWorkingDaysLost(numDays, periods);
    cout << "{ ";
    for (int period:periods)
    {
        cout << period << ' ';
    }
    cout << "} in " << numDays << "-day period: ";
    cout << "expected " << expected << ", got " << actual << endl;
}

int main()
{
    /*
    vector<int> v1 = {3, 4, 8};
    testGetNumWorkingDaysLost(14, v1, 5);
    vector<int> v2 = {12, 15, 25, 40};
    testGetNumWorkingDaysLost(100, v2, 15);

    return 0;
    */
    int numTestCases; /* T */
    int numDays;  /* 7 ≤ N ≤ 3650 */
    int numParties;  /* 1 ≤ P ≤ 100 */
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; ++i)
    {
        cin >> numDays >> numParties;
        vector<int> periods(numParties);
        for (auto &period:periods)
        {
            cin >> period;
        }
        int daysLost = getNumWorkingDaysLost(numDays, periods);
        cout << daysLost << endl;
    }
    return 0;
}
