#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

using namespace std;

int main()
{
    int numTestCases;
    cin >> numTestCases;
    // consume newline characters
    getchar(), getchar();
    for (int i = 0; i < numTestCases; ++i)
    {
        if (i != 0)
        {
            cout << endl;
        }

        map<string, unsigned> speciesList; // no more than 10,000 species
        long numTrees = 0; // no more than 1,000,000 trees
        string tree; // No species name exceeds 30 characters
        getline(cin, tree);
        while (!tree.empty())
        {
            ++numTrees;
            auto it = speciesList.find(tree);
            if (it == speciesList.end())
            {
                speciesList.insert(pair<string, unsigned>(tree, 1));
            }
            else
            {
                ++(it->second);
            }
            getline(cin, tree);
        }
        for (const auto &pair:speciesList)
        {
            cout << pair.first << ' ' << fixed << setprecision(4)
                 << 100 * pair.second / (double) numTrees << endl;
        }
    }
    return 0;
}
