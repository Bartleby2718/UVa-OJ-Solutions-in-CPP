#include <iostream>
#include <vector>

using namespace std;

struct Object
{
    int price;
    int weight;

    Object(int price, int weight) : price(price), weight(weight)
    {
    }
};

int knapsack(const vector<Object>& objects, int maxWeight)
{
    int n = objects.size();
    int table[n + 1][maxWeight + 1];

    for (int i = 0; i < n + 1; ++i)
    {
        table[i][0] = 0;
    }

    for (int weight = 0; weight <= maxWeight; ++weight)
    {
        table[0][weight] = 0;
    }

    for (int i = 1; i < n + 1; ++i)
    {
        for (int weight = 1; weight <= maxWeight; ++weight)
        {
            int excluded = table[i - 1][weight];
            Object object = objects.at(i - 1);
            if (object.weight <= weight)
            {
                int included = table[i - 1][weight - object.weight] + object.price;
                table[i][weight] = max(included, excluded);
            }
            else
            {
                table[i][weight] = excluded;
            }
        }
    }
    return table[n][maxWeight];
}

int getMaxValue(const vector<Object>& objects, vector<int>& maxWeights)
{
    int sum = 0;
    for (int weight:maxWeights)
    {
        int value = knapsack(objects, weight);
        sum += value;
    }
    return sum;
}

int main()
{
    int numTestCases; // 1 ≤ T ≤ 1000
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; ++i)
    {
        int numObjects; // 1 ≤ N ≤ 1000
        cin >> numObjects;
        vector<Object> objects;
        int price, weight; // 1 ≤ P ≤ 100, // 1 ≤ W ≤ 30
        for (int j = 0; j < numObjects; ++j)
        {
            cin >> price >> weight;
            objects.emplace_back(price, weight);
        }

        int numPeople, maxWeight; // 1 ≤ G ≤ 100, 1 ≤ MW ≤ 30
        cin >> numPeople;
        vector<int> maxWeights;
        for (int j = 0; j < numPeople; ++j)
        {
            cin >> maxWeight;
            maxWeights.push_back(maxWeight);
        }
        int maxValue = getMaxValue(objects, maxWeights);
        cout << maxValue << endl;
    }
    return 0;
}
