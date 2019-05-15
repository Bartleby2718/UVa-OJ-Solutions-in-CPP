#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Maker
{
public:
    Maker(string &name, long lowest, long highest)
            : name(name), lowest(lowest), highest(highest)
    {
    }

    Maker() = default;

    string name;
    long lowest;
    long highest;
};


string getMakerWithinRange(vector<Maker> &v1, long queryPrice)
{
    bool alreadyFoundOnce = false;
    string makerWithinRange = "UNDETERMINED";
    for (auto &maker:v1)
    {
        if (maker.lowest <= queryPrice && queryPrice <= maker.highest)
        {
            if (alreadyFoundOnce)
            {
                makerWithinRange = "UNDETERMINED";
                break;
            }
            else
            {
                alreadyFoundOnce = true;
                makerWithinRange = maker.name;
            }
        }
    }
    return makerWithinRange;
}

int main()
{
    string maker;  // contains no whitespace and will never exceeds 20 characters
    long lowest, highest;  //0 < L < H < 1000000
    int numTestCases; // T ≤ 10
    int databaseSize; // D < 10000
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; ++i)
    {
        if (i != 0)
        {
            cout << endl;
        }
        cin >> databaseSize;
        vector<Maker> v1(databaseSize);
        for (int j = 0; j < databaseSize; ++j)
        {
            cin >> maker >> lowest >> highest;
            v1.at(j) = Maker(maker, lowest, highest);
        }
        int numQueries;  // Q < 1000
        cin >> numQueries;
        long queryPrice;  // 0 < P < 1000000
        string output;
        for (int j = 0; j < numQueries; ++j)
        {
            cin >> queryPrice;
            output = getMakerWithinRange(v1, queryPrice);
            cout << output << endl;
        }
    }
    return 0;
}