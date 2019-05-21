#include <iostream>
#include <vector>

using namespace std;

int getNumCrossed(int ferryLength, const vector<int> &leftCars, const vector<int> &rightCars)
{
    bool leftToRight = true;
    auto leftIterator = leftCars.begin();
    auto rightIterator = rightCars.begin();
    int numCrossed = 0;
    while (!(leftIterator == leftCars.end() && rightIterator == rightCars.end()))
    {
        if (leftToRight)
        {
            for (int sum = 0;
                 leftIterator != leftCars.end() && (sum + *leftIterator <= ferryLength); ++leftIterator)
            {
                sum += *leftIterator;
            }
        }
        else
        {
            for (int sum = 0;
                 rightIterator != rightCars.end() && (sum + *rightIterator <= ferryLength); ++rightIterator)
            {
                sum += *rightIterator;
            }
        }
        leftToRight = !leftToRight;
        ++numCrossed;
    }
    return numCrossed;
}

int main()
{
    int numCases;
    cin >> numCases;
    for (int i = 0; i < numCases; ++i)
    {
        int ferryLength, numCars;  // length in meters
        cin >> ferryLength >> numCars;
        vector<int> leftCars, rightCars;
        for (int j = 0; j < numCars; ++j)
        {
            int carLength;
            string direction;
            cin >> carLength >> direction;
            if (direction == "left")
            {
                leftCars.push_back(carLength);
            }
            else if (direction == "right")
            {
                rightCars.push_back(carLength);
            }
        }
        int numCrossed = getNumCrossed(ferryLength * 100, leftCars, rightCars);
        cout << numCrossed << endl;
    }
    return 0;
}
