#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

bool canBePartitioned(const vector<int>& weights)
{
    int n = weights.size();
    int total = 0;
    for (int weight:weights)
    {
        total += weight;
    }
    if (total % 2 != 0)
    {
        return false;
    }
    total /= 2; // the target is half the total
    bool table[n + 1][total + 1];

    for (int i = 0; i <= n; ++i)
    {
        table[i][0] = true;
    }
    for (int j = 1; j <= total; ++j)
    {
        table[0][j] = false;
    }

    for (int i = 1; i <= n; ++i)
    {
        for (int sum = 1; sum <= total; ++sum)
        {
            bool excluded = table[i - 1][sum];
            int weight = weights.at(i - 1);
            if (weight <= sum)
            {
                bool included = table[i - 1][sum - weight];
                table[i][sum] = included || excluded;
            }
            else
            {
                table[i][sum] = excluded;
            }
        }
    }
    return table[n][total];
}

int main()
{
    int numTestCases; // m
    cin >> numTestCases;
    getchar(); // consume newline character
    for (int i = 0; i < numTestCases; ++i)
    {
        string line;
        getline(cin, line);
        stringstream ss(line);
        vector<int> weights; // 1 ≤ n ≤ 20, sum ≤ 200
        int weight;
        while (ss >> weight)
        {
            weights.push_back(weight);
        }
        bool result = canBePartitioned(weights);
        cout << (result ? "YES" : "NO") << endl;
    }
    return 0;
}
