#include <iostream>
#include <map>
#include <vector>

using namespace std;

// got a lot of help from https://www.geeksforgeeks.org/min-max-range-queries-array/
struct Node
{
    long value;
    long count;
    long from;
    long to;

    Node(long value, long count, long from, long to) : value(value), count(count), from(from), to(to)
    {
    }
};

long mostFrequent(const vector<Node *> &nodes, const long nodeIndex, const long from, const long to)
{
    Node *node = nodes.at(nodeIndex);
    if (from == node->from && to == node->to)
    {
        return node->count;
    }
    else
    {
        if (nodeIndex >= nodes.size() / 2) // leaf
        {
            return to - from + 1;
        }

        // not leaf -> has two children because the original tree is full
        long leftIndex = 2 * nodeIndex + 1, rightIndex = 2 * nodeIndex + 2;
        Node *left = nodes.at(leftIndex), *right = nodes.at(rightIndex);
        if (to <= left->to) // only from the left subtree
        {
            return mostFrequent(nodes, leftIndex, from, to);
        }
        else if (from >= right->from) // only from the right subtree
        {
            return mostFrequent(nodes, rightIndex, from, to);
        }
        else // spans both subtrees
        {
            long leftCount = mostFrequent(nodes, leftIndex, from, left->to);
            long rightCount = mostFrequent(nodes, rightIndex, right->from, to);
            return (leftCount > rightCount) ? leftCount : rightCount;
        }
    }
}

unsigned long biggestPowerOfTwo(unsigned long upperLimit)
{
    /** returns the biggest (power of two - 1) less than upperLimit */
    long value = 0;
    while (value < upperLimit)
    {
        value = 2 * value + 1;
    }
    return value / 2;
}

int main()
{
    long numInts, numQueries; // 1 ≤ n, q ≤ 100000
    long from, to; // 1 ≤ i ≤ j ≤ n (one-based)
    cin >> numInts;
    while (numInts != 0)
    {
        cin >> numQueries;
        long value, count;
        map<long, long> occurrences;
        for (long i = 0; i < numInts; ++i)
        {
            cin >> value; // −100000 ≤ a_i ≤ 100000
            if (occurrences.find(value) == occurrences.end())
            {
                occurrences.insert(make_pair(value, 1));
            }
            else
            {
                ++occurrences.at(value);
            }
        }
        long cumulativeCount = 0;
        vector<Node *> nodes(2 * occurrences.size() - 1);
        long nodeIndex = biggestPowerOfTwo(nodes.size()); // start from the bottom left leaf
        for (auto pair:occurrences)
        {
            tie(value, count) = pair;
            from = cumulativeCount;
            to = (cumulativeCount += count) - 1;
            nodes.at(nodeIndex) = new Node(value, count, from, to);
            // move to the next leaf
            ++nodeIndex;
            if (nodeIndex == nodes.size())
            {
                nodeIndex = occurrences.size() - 1;
            }
        }
        for (long i = occurrences.size() - 2; i >= 0; --i)
        {
            Node *left = nodes.at(2 * i + 1);
            Node *right = nodes.at(2 * i + 2);
            if (left->count > right->count)
            {
                nodes.at(i) = new Node(left->value, left->count, left->from, right->to);
            }
            else
            {
                nodes.at(i) = new Node(right->value, right->count, left->from, right->to);
            }
        }

        for (long i = 0; i < numQueries; ++i)
        {
            cin >> from >> to; // one-based
            long rootIndex = 0;
            long numOccurrences = mostFrequent(nodes, rootIndex, from - 1, to - 1);
            cout << numOccurrences << endl;
        }
        cin >> numInts;
    }
    return 0;
}
