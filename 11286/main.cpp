#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int main()
{
    int numFroshes; // 1 ≤ n ≤ 10000
    cin >> numFroshes;
    while (numFroshes != 0)
    {
        map<string, unsigned> m;
        unsigned max = 1;
        for (int i = 0; i < numFroshes; ++i)
        {
            string courses[5]; // five distinct courses selected by the frosh, an integer between 100 and 499
            for (auto &course : courses)
            {
                cin >> course;
            }
            sort(courses, courses + 5);
            string key = courses[0] + courses[1] + courses[2] + courses[3] + courses[4];
            auto it = m.find(key);
            if (it == m.end())
            {
                m.insert(make_pair(key, 1));
            }
            else
            {
                unsigned value = ++(it->second);
                if (value > max)
                {
                    max = value;
                }
            }
        }
        unsigned biggest = count_if(m.begin(), m.end(),
                                    [max](pair<string, unsigned> entry) { return entry.second == max; });
        cout << biggest * max << endl;
        cin >> numFroshes;
    }
    return 0;
}
