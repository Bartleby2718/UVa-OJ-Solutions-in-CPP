#include <iostream>
#include <vector>

using namespace std;

int getSteps(vector<char> &grid, int length)
{
    int longestPathLength = 0;
    for (int i = 0; i < grid.size(); ++i)
    {
        int start = grid[i];
        if (start == '1')
        {
            // get the shortest distance from the selected initial state
            int minimumDistanceFrom1 = 2 * length;
            for (int j = 0; j < grid.size() && minimumDistanceFrom1 > 1; ++j)
            {
                int end = grid[j];
                if (end == '3')
                {
                    int horizontal = abs(i % length - j % length);
                    int vertical = abs(i / length - j / length);
                    int distance = horizontal + vertical;
                    if (distance < minimumDistanceFrom1)
                    {
                        minimumDistanceFrom1 = distance;
                    }
                }
            }
            // update if the distance is longer than that from another initial state
            if (minimumDistanceFrom1 > longestPathLength)
            {
                longestPathLength = minimumDistanceFrom1;
            }
        }
    }
    return longestPathLength;
}

int main()
{
    int length;
    while (cin >> length)
    {
        vector<char> grid(length * length);
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < length; ++j)
            {
                cin >> grid.at(i * length + j);
            }
        }
        int steps = getSteps(grid, length);
        cout << steps << endl;
    }
    return 0;
}
