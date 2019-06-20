#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Result
{
    bool matched;
    long from;
    long to;

    Result(bool matched, long from, long to)
            : matched(matched), from(from), to(to)
    {
    }
};

long getVectorIndex(char c)
{
    return isupper(c) ? (c - 'A') : (c - 'a' + 26);
}

Result checkSubsequence(vector<vector<long>> &v, const string &query)
{
    Result notFound = {false, 0, 0};
    Result found = {true, 0, 0};
    long previousIndex = 0;
    for (long i = 0; i < query.size(); ++i)
    {
        char c = query[i];
        int vectorIndex = getVectorIndex(c);
        auto it = lower_bound(v.at(vectorIndex).begin(), v.at(vectorIndex).end(), previousIndex);
        if (it == v.at(vectorIndex).end())
        {
            return notFound;
        }
        else
        {
            long charIndex = *it;
            previousIndex = charIndex + 1;
            found.to = charIndex;
            if (i == 0)
            {
                found.from = charIndex;
            }
        }
    }
    return found;
}

int main()
{
    // a string S containing only alphabets. The length of this string is at most 1000000
    char c;
    long index = 0;
    vector<vector<long>> alphabets(52);
    while (c = getchar(), c != '\n')
    {
        int vectorIndex = getVectorIndex(c);
        alphabets.at(vectorIndex).push_back(index++);
    }
    int numQueries; // 0 < Q < 3501
    cin >> numQueries;
    for (int i = 0; i < numQueries; ++i)
    {
        string query; //  string SS of length less than 101
        cin >> query;
        Result result = checkSubsequence(alphabets, query);
        if (result.matched)
        {
            cout << "Matched " << result.from << ' ' << result.to << endl;
        }
        else
        {
            cout << "Not matched" << endl;
        }
    }
    return 0;
}
