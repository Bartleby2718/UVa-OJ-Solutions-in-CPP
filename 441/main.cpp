#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void print6(const vector<int> &values)
{
    int numValues = values.size();
    // generating combinations: https://stackoverflow.com/a/9430993/4370146
    vector<bool> booleans(numValues);
    fill(booleans.begin(), booleans.begin() + 6, true);
    do
    {
        bool isFirst = true;
        for (int i = 0; i < numValues; ++i)
        {
            bool isFilled = booleans[i];
            if (isFilled)
            {
                // blank space between numbers
                if (isFirst)
                {
                    isFirst = false;
                }
                else
                {
                    cout << ' ';
                }
                int value = values[i];
                cout << value;
            }
        }
        cout << endl;
    } while (prev_permutation(booleans.begin(), booleans.end()));
}

int main()
{
    int numValues;  // 6 < k < 13
    cin >> numValues;
    bool isFirst = true;
    while (numValues != 0)
    {
        // leading blank line (optional)
        if (isFirst)
        {
            isFirst = false;
        }
        else
        {
            cout << endl;
        }

        vector<int> values(numValues);
        for (int i = 0; i < numValues; ++i)
        {
            cin >> values[i];
        }
        print6(values);
        cin >> numValues;
    }
    return 0;
}
