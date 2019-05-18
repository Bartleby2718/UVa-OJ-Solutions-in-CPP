#include <functional>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

long getMinimumTotalCost(priority_queue<long, vector<long>, greater<long>> &operands)
{
    long totalCost = 0;
    while (operands.size() >= 2)  // guaranteed to be >= 2, decrements by 1 in every iteration
    {
        long operand1 = operands.top();
        operands.pop();
        long operand2 = operands.top();
        operands.pop();
        long cost = operand1 + operand2;
        totalCost += cost;
        operands.push(cost);
    }
    return totalCost;
}

int main()
{
    int numOperands;  // 2 ≤ N ≤ 5000
    cin >> numOperands;
    while (numOperands != 0)
    {
        priority_queue<long, vector<long>, greater<long>> operands;  // all are less than 100000
        for (int i = 0; i < numOperands; ++i)
        {
            long operand;
            cin >> operand;
            operands.push(operand);
        }
        long minimumTotalCost = getMinimumTotalCost(operands);
        cout << minimumTotalCost << endl;
        cin >> numOperands;
    }
    return 0;
}
