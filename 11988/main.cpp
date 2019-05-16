#include <iostream>
#include <list>

using namespace std;

int main()
{
    list<char> l1;
    auto iterator = l1.begin();
    char c;
    while (cin >> noskipws >> c)
    {
        if (c == '\n')
        {
            for (auto output:l1)
            {
                cout << output;
            }
            cout << endl;
            list<char> newList;
            l1 = newList;
            iterator = l1.begin();
        }
        else if (c == '[')
        {
            iterator = l1.begin();
        }
        else if (c == ']')
        {
            iterator = l1.end();
        }
        else
        {
            l1.insert(iterator, c);
        }
    }
    return 0;
}
