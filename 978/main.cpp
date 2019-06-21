#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int numTestCases; // 1 ≤ N ≤ 100
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; ++i)
    {
        if (i != 0) // There should also be a blank line between test cases
        {
            cout << endl;
        }

        long numBattlefields, numGreen, numBlue; // 1 ≤ B, SG, SB ≤ 100,000
        cin >> numBattlefields >> numGreen >> numBlue;
        priority_queue<int> green, blue;
        int power; //  a positive integer smaller than 101
        for (long j = 0; j < numGreen; ++j)
        {
            cin >> power;
            green.push(power);
        }
        for (long j = 0; j < numBlue; ++j)
        {
            cin >> power;
            blue.push(power);
        }

        while (!green.empty() && !blue.empty())
        {
            vector<int> greenOnBattlefields, blueOnBattlefields;
            for (long j = 0; j < numBattlefields && !green.empty() && !blue.empty(); ++j)
            {
                int greenSoldier = green.top(), blueSoldier = blue.top();
                green.pop(), blue.pop();
                greenOnBattlefields.push_back(greenSoldier);
                blueOnBattlefields.push_back(blueSoldier);
            }

            for (long j = 0; j < greenOnBattlefields.size(); ++j)
            {
                int greenSoldier = greenOnBattlefields[j];
                int blueSoldier = blueOnBattlefields[j];
                if (greenSoldier > blueSoldier)
                {
                    green.push(greenSoldier - blueSoldier);
                }
                else if (greenSoldier < blueSoldier)
                {
                    blue.push(blueSoldier - greenSoldier);
                }
            }
        }

        if (green.empty() && blue.empty())
        {
            cout << "green and blue died" << endl;
        }
        else if (blue.empty())
        {
            cout << "green wins" << endl;
            while (!green.empty())
            {
                cout << green.top() << endl;
                green.pop();
            }
        }
        else if (green.empty())
        {
            cout << "blue wins" << endl;
            while (!blue.empty())
            {
                cout << blue.top() << endl;
                blue.pop();
            }
        }
    }
    return 0;
}
