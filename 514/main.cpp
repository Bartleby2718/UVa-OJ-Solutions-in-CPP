#include <iostream>
#include <vector>

using namespace std;

bool canMarshal(vector<int> &coaches)
{
    vector<int> queue1;
    for (int i = 1; i <= coaches.size(); ++i)
    {
        queue1.push_back(i);
    }

    vector<int> stack1;
    int max = 0;
    for (auto current:coaches)
    {
        if (current > max)
        {
            for (int i = 0; i < current - max; ++i)
            {
                if (queue1.empty())
                {
                    return false;
                }
                else
                {
                    int element = queue1.front();
                    stack1.push_back(element);
                    queue1.erase(queue1.begin());
                }
            }
            stack1.pop_back();
            max = current;
        }
        else if (current == stack1.back())
        {
            stack1.pop_back();
        }
        else
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int numCoaches;
    cin >> numCoaches;
    while (numCoaches != 0)
    {
        int coach;
        cin >> coach;
        while (coach != 0)
        {
            vector<int> coaches(numCoaches);
            coaches.at(0) = coach;
            for (auto iterator = coaches.begin() + 1; iterator != coaches.end(); ++iterator)
            {
                cin >> *iterator;
            }
            bool possible = canMarshal(coaches);
            cout << (possible ? "Yes" : "No") << endl;
            cin >> coach;
        }
        cout << endl;
        cin >> numCoaches;
    }
    return 0;
}
