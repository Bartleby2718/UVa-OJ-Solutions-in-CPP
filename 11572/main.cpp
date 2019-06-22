#include <iostream>
#include <map>

using namespace std;

// got the idea from https://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/
int main()
{
    int numTestCases;
    cin >> numTestCases;
    // no more than one million total snowflakes
    for (int i = 0; i < numTestCases; ++i)
    {
        map<long, long> snowflakeIndices;
        long numSnowflakes;
        cin >> numSnowflakes;
        long maxSize = 0, currentSize = 0, startOfPackage = 0;
        for (long j = 0; j < numSnowflakes; ++j)
        {
            long snowflakeId;
            cin >> snowflakeId;
            auto it = snowflakeIndices.find(snowflakeId);
            if (it == snowflakeIndices.end()) // not found
            {
                snowflakeIndices.insert(pair<long, long>(snowflakeId, j));
                ++currentSize;
            }
            else // duplicate found
            {
                // record current size
                if (currentSize > maxSize)
                {
                    maxSize = currentSize;
                }
                // and start a new streak
                if (it->second > startOfPackage)
                {
                    startOfPackage = it->second;
                }
                // update size and index
                currentSize = j - startOfPackage;
                it->second = j;
            }
        }
        // update maxSize in case there were no duplicates in the last package
        if (currentSize > maxSize)
        {
            maxSize = currentSize;
        }
        cout << maxSize << endl;
    }
    return 0;
}
