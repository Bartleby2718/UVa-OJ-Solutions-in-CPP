#include <iostream>

using namespace std;

int main()
{
    int numCases;
    cin >> numCases;
    char newLine;
    cin >> noskipws >> newLine; // consume trailing newline character
    for (int i = 0; i < numCases; ++i)
    {
        string line;
        getline(cin, line);
        int numM = 0, numF = 0;
        for (char c:line)
        {
            switch (c)
            {
                case 'M':
                    ++numM;
                    break;
                case 'F':
                    ++numF;
                    break;
                default:
                    break;
            }
        }
        cout << ((numM == numF && numF != 1) ? "LOOP" : "NO LOOP") << endl;
    }
    return 0;
}
