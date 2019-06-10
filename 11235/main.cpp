#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

long mostFrequent(const vector<long> &ints, const long from, const long to)
{
    unordered_map<long, long> occurrences;
    for (long index = from - 1; index <= to - 1; ++index)
    {
        long value = ints.at(index);
        ++occurrences[value];
    }
    priority_queue<long> pq; // maximum priority queue by default
    for (auto value:occurrences)
    {
        pq.push(value.second);
    }
    return pq.top();
}

int main()
{
    long numInts, numQueries; // 1 ≤ n, q ≤ 100000
    long from, to; // 1 ≤ i ≤ j ≤ n
    cin >> numInts;
    while (numInts != 0)
    {
        cin >> numQueries;
        vector<long> ints(numInts); // already sorted in non-decreasing order
        for (long i = 0; i < numInts; ++i)
        {
            cin >> ints[i]; // −100000 ≤ a_i ≤ 100000
        }
        for (long i = 0; i < numQueries; ++i)
        {
            cin >> from >> to;
            long numOccurrences = mostFrequent(ints, from, to);
            cout << numOccurrences << endl;
        }
        cin >> numInts;
    }
    return 0;
}
