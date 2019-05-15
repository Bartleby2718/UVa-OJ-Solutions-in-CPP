#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class driveRatio
{
public:
    driveRatio() = default;

    driveRatio(int denominator, int numerator) : denominator(denominator), numerator(numerator)
    {
        value = numerator / (double) denominator;
    }

    bool operator<(const driveRatio &s2) const
    {
        return numerator * s2.denominator < s2.numerator * denominator;
    }

    int denominator;
    int numerator;
    double value;
};

string getMaximumSpread(vector<int> &frontSprockets, vector<int> &rearSprockets)
{
    // 1. sort ratios
    vector<driveRatio> driveRatios;
    for (auto &front:frontSprockets)
    {
        for (auto &rear:rearSprockets)
        {
            driveRatio newOne(front, rear);
            driveRatios.push_back(newOne);
        }
    }
    sort(driveRatios.begin(), driveRatios.end(), less<driveRatio>());

    // 2. get spreads
    int numDriveRatios = driveRatios.size();
    vector<double> spreads(numDriveRatios - 1);
    for (int i = 1; i < numDriveRatios; ++i)
    {
        driveRatio one = driveRatios.at(i);
        driveRatio another = driveRatios.at(i - 1);
        double spread = one.value / another.value;
        spreads.at(i - 1) = spread;
    }

    // 3. pick the maximum element
    auto iterator = max_element(begin(spreads), end(spreads));
    double maximumSpread = *iterator;

    // 4. round to two decimal places
    stringstream stream;
    stream << fixed << setprecision(2) << maximumSpread;
    return stream.str();
}

int main()
{
    int numFrontSprockets, numRearSprockets;  // both < 10
    cin >> numFrontSprockets;
    while (numFrontSprockets != 0)
    {
        cin >> numRearSprockets;

        vector<int> frontSprockets(numFrontSprockets);
        for (int i = 0; i < numFrontSprockets; ++i)
        {
            cin >> frontSprockets.at(i);  // 10 <= numTeeth <= 100
        }

        vector<int> rearSprockets(numRearSprockets);
        for (int j = 0; j < numRearSprockets; ++j)
        {
            cin >> rearSprockets.at(j);  // 10 <= numTeeth <= 100
        }

        string result = getMaximumSpread(frontSprockets, rearSprockets);
        cout << result << endl;
        cin >> numFrontSprockets;
    }
    return 0;
}
