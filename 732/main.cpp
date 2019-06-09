#include <iostream>
#include <vector>

using namespace std;

void getInstructions(vector<vector<bool>> &instructions, vector<char> stack1, const string &source,
                     const string &target, vector<bool> pushOrNot, string output, int sourceIndex, int targetIndex)
{
    while (sourceIndex < source.length())
    {
        char sourceChar = source[sourceIndex];
        char targetChar = target[targetIndex];
        if (stack1.empty() || stack1.back() != targetChar) // must push
        {
            pushOrNot.push_back(true);
            stack1.push_back(sourceChar);
            ++sourceIndex;
        }
        else // either push to the stack or pop from the stack
        {
            // Choice 1. push to the stack
            pushOrNot.push_back(true);
            stack1.push_back(sourceChar);
            ++sourceIndex;
            getInstructions(instructions, stack1, source, target, pushOrNot, output, sourceIndex, targetIndex);

            // Choice 2. roll back
            pushOrNot.pop_back();
            stack1.pop_back();
            --sourceIndex;
            // and pop from the stack
            pushOrNot.push_back(false);
            char recentlyPushed = stack1.back();
            stack1.pop_back();
            output += recentlyPushed;
            ++targetIndex;
        }
    }
    // went through every character in the source
    // you can now only pop from the stack
    while (!stack1.empty())
    {
        pushOrNot.push_back(false);
        output += stack1.back();
        stack1.pop_back();
    }
    // final check
    if (output == target)
    {
        instructions.push_back(pushOrNot);
    }
}

int main()
{
    string source, target;
    while (cin >> source >> target)
    {
        vector<vector<bool>> instructions;
        vector<char> stack1;
        vector<bool> pushOrNot;
        string output;
        int sourceIndex = 0, targetIndex = 0;
        getInstructions(instructions, stack1, source, target, pushOrNot, output, sourceIndex, targetIndex);
        cout << '[' << endl;
        for (const vector<bool> &instruction:instructions)
        {
            for (int i = 0; i < instruction.size(); ++i)
            {
                if (i != 0)
                {
                    cout << ' ';
                }
                cout << (instruction[i] ? 'i' : 'o');
            }
            cout << endl;
        }
        cout << ']' << endl;
    }
    return 0;
}
