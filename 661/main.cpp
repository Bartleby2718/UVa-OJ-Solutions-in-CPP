#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int numDevices; // n ≤ 20
    int numOperations; // m
    int capacity; // capacity of the fuse (in Amperes)
    cin >> numDevices >> numOperations >> capacity;
    int testIndex = 0;
    while (!(numDevices == 0 && numOperations == 0 && capacity == 0))
    {
        cout << "Sequence " << ++testIndex << endl;
        int consumptions[numDevices]; // positive integer (in Amperes)
        for (int i = 0; i < numDevices; ++i)
        {
            cin >> consumptions[i];
        }

        vector<bool> states(numDevices); // use vector because VLAs may not be initialized
        bool blown = false;
        int maxConsumption = 0, currentConsumption = 0;
        for (int i = 0; i < numOperations; ++i)
        {
            int oneBasedIndex; // between 1 and n inclusive.
            cin >> oneBasedIndex;
            states[oneBasedIndex - 1] = !states[oneBasedIndex - 1];
            if (states[oneBasedIndex - 1]) // turned on
            {
                currentConsumption += consumptions[oneBasedIndex - 1];
                if (currentConsumption > maxConsumption)
                {
                    maxConsumption = currentConsumption;
                    if (!blown && maxConsumption > capacity)
                    {
                        blown = true;
                        cout << "Fuse was blown." << endl << endl;
                    }
                }
            }
            else // turned off
            {
                currentConsumption -= consumptions[oneBasedIndex - 1];
            }
        }
        if (!blown)
        {
            cout << "Fuse was not blown.\nMaximal power consumption was "
                 << maxConsumption << " amperes." << endl << endl;
        }
        cin >> numDevices >> numOperations >> capacity;
    }
    return 0;
}
