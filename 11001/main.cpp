#include <iostream>

using namespace std;

int getMaxNumDiscs(long totalVolume, int minimumVolume)
{
    long maxNumDiscs = 0;
    long valueToCompare = 0;
    long maxValue = 0;
    // rule out cases where V < V_0 with proper upper limit of numDiscs
    long numDiscLimit = totalVolume / minimumVolume;
    for (long numDiscs = 1; numDiscs <= numDiscLimit; ++numDiscs)
    {
        // total length = numDiscs * 0.3 * sqrt(totalVolume / numDiscs - minimumVolume)
        // for precision, compare the value inside the square bracket (and ignore 0.3)
        valueToCompare = numDiscs * (totalVolume - minimumVolume * numDiscs);
        if (valueToCompare > maxValue)
        {
            maxNumDiscs = numDiscs;
            maxValue = valueToCompare;
        }
        else if (valueToCompare != 0 && valueToCompare == maxValue)
        {
            maxNumDiscs = 0;
            break;
        }
    }
    return maxNumDiscs;
}

int main()
{
    long totalVolume;  // 0 < V_total ≤ 60000
    int minimumVolume;  // 0 < V_0 ≤ 600
    cin >> totalVolume >> minimumVolume;
    while (!(totalVolume == 0 && minimumVolume == 0))
    {
        int numDiscs = getMaxNumDiscs(totalVolume, minimumVolume);
        cout << numDiscs << endl;
        cin >> totalVolume >> minimumVolume;
    }
    return 0;
}
