#include <algorithm>
#include <iostream>

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

Result checkSubsequence(const string &candidates, const string &query)
{
    Result notFound(false, 0, 0);
    auto originalBegin1 = candidates.begin();
    auto begin1 = candidates.begin();
    auto end1 = candidates.end();
    auto begin2 = query.begin();
    auto end2 = query.end();
    auto it = find(begin1, end1, *begin2);
    if (it == end1)
    {
        return notFound;
    }

    long index = it - begin1;
    Result r = {true, index, index};
    begin1 = it + 1;
    ++begin2;
    while (begin1 != end1 && begin2 != end2)
    {
        it = find(begin1, end1, *begin2);
        if (it == end1)
        {
            return notFound;
        }

        r.to = it - originalBegin1;
        begin1 = it + 1;
        ++begin2;
    }
    return (begin2 == end2) ? r : notFound;
}

int main()
{
    string candidates; // a string S containing only alphabets. The length of this string is at most 1000000
    cin >> candidates;
    int numQueries; // 0 < Q < 3501
    cin >> numQueries;
    for (int i = 0; i < numQueries; ++i)
    {
        string query; //  string SS of length less than 101
        cin >> query;
        Result result = checkSubsequence(candidates, query);
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
