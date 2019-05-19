#include <iostream>
#include <queue>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

bool checkQueue(vector<int> &commands, vector<int> &elements)
{
    queue<int> q;
    int numCommands = commands.size();
    bool canBeQueue = true;
    for (int i = 0; i < numCommands && canBeQueue; ++i)
    {
        int command = commands[i];
        int element = elements[i];
        if (command == 1)
        {
            q.push(element);
        }
        else if (command == 2)
        {
            canBeQueue = !q.empty() && q.front() == element;
            if (canBeQueue)
            {
                q.pop();
            }
        }
    }
    return canBeQueue;
}

template<class T>
bool checkStackOrPriorityQueue(T s, vector<int> &commands, vector<int> &elements)
{
    int numCommands = commands.size();
    bool canBe = true;
    for (int i = 0; i < numCommands && canBe; ++i)
    {
        int command = commands[i];
        int element = elements[i];
        if (command == 1)
        {
            s.push(element);
        }
        else if (command == 2)
        {
            canBe = !s.empty() && s.top() == element;
            if (canBe)
            {
                s.pop();
            }
        }
    }
    return canBe;
}

tuple<bool, bool, bool> tryAll(vector<int> &commands, vector<int> &elements)
{
    bool canBeStack = checkStackOrPriorityQueue(stack<int>(), commands, elements);
    bool canBeQueue = checkQueue(commands, elements);
    bool canBePriorityQueue = checkStackOrPriorityQueue(priority_queue<int>(), commands, elements);
    return make_tuple(canBeStack, canBeQueue, canBePriorityQueue);
}

string determineDataStructure(bool canBeStack, bool canBeQueue, bool canBePriorityQueue)
{
    if (canBeStack && !canBeQueue && !canBePriorityQueue)
    {
        return "stack";
    }
    else if (!canBeStack && canBeQueue && !canBePriorityQueue)
    {
        return "queue";
    }
    else if (!canBeStack && !canBeQueue && canBePriorityQueue)
    {
        return "priority queue";
    }
    else if (!canBeStack && !canBeQueue && !canBePriorityQueue)
    {
        return "impossible";
    }
    else
    {
        return "not sure";
    }
}

int main()
{
    int numCommands;  // 1 ≤ n ≤ 1000
    while (cin >> numCommands)
    {
        vector<int> commands(numCommands);  // 1 or 2
        vector<int> elements(numCommands);  // positive integer not larger than 100
        for (int i = 0; i < numCommands; ++i)
        {
            cin >> commands[i] >> elements[i];
        }
        bool canBeStack, canBeQueue, canBePriorityQueue;
        tie(canBeStack, canBeQueue, canBePriorityQueue) = tryAll(commands, elements);
        string answer = determineDataStructure(canBeStack, canBeQueue, canBePriorityQueue);
        cout << answer << endl;
    }
    return 0;
}
