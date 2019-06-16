#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

long greatestPowerOfTwo(long strictUpperLimit)
{
    long value = 0;
    while (2 * value + 1 < strictUpperLimit)
    {
        value = 2 * value + 1;
    }
    return value;
}

class Node
{
    long from;
    long to;
    long numBuccaneers;
public:
    Node(long from, long to, long numBuccaneers)
            : from(from), to(to), numBuccaneers(numBuccaneers)
    {
    }

    friend class SegmentTree;
};

class SegmentTree
{
    vector<Node *> nodes;
public:
    SegmentTree(string &pirates, set<long> &branches);

    void updateAncestors(long nodeIndex);

    void toBuccaneer(long index1, long index2);

    void toBarbary(long index1, long index2);

    void toInverse(long index1, long index2);

    long getNumBuccaneer(long nodeIndex, long index1, long index2);
};

SegmentTree::SegmentTree(string &pirates, set<long> &branches)
{
    long numLeafNodes = branches.size() - 1;
    long numNodes = 2 * numLeafNodes - 1;
    nodes.resize(numNodes);
    // create leaf nodes
    long nodeIndex = greatestPowerOfTwo(numNodes);
    for (auto it = branches.begin(); next(it) != branches.end(); ++it)
    {
        long numBuccaneers = 0;
        long current = *it, nextFrom = *next(it);
        for (long i = current; i < nextFrom; ++i)
        {
            if (pirates[i] == '1')
            {
                ++numBuccaneers;
            }
        }
        if (nodeIndex == numNodes)
        {
            nodeIndex = numLeafNodes - 1;
        }
        nodes.at(nodeIndex++) = new Node(current, nextFrom - 1, numBuccaneers);
    }
    // create internal nodes
    for (nodeIndex = numLeafNodes - 2; nodeIndex >= 0; --nodeIndex)
    {
        Node *left = nodes.at(2 * nodeIndex + 1);
        Node *right = nodes.at(2 * nodeIndex + 2);
        long numBuccaneer = left->numBuccaneers + right->numBuccaneers;
        nodes.at(nodeIndex) = new Node(left->from, right->to, numBuccaneer);
    }
}

void SegmentTree::toBuccaneer(long index1, long index2)
{
    for (long i = nodes.size() / 2; i < nodes.size(); ++i)
    {
        Node *node = nodes.at(i);
        if (index1 <= node->from && node->to <= index2)
        {
            node->numBuccaneers = node->to - node->from + 1;
            updateAncestors(i);
        }
    }
}

void SegmentTree::toBarbary(long index1, long index2)
{
    for (long i = nodes.size() / 2; i < nodes.size(); ++i)
    {
        Node *node = nodes.at(i);
        if (index1 <= node->from && node->to <= index2)
        {
            node->numBuccaneers = 0;
            updateAncestors(i);
        }
    }
}

void SegmentTree::toInverse(long index1, long index2)
{
    for (long i = nodes.size() / 2; i < nodes.size(); ++i)
    {
        Node *node = nodes.at(i);
        if (index1 <= node->from && node->to <= index2)
        {
            node->numBuccaneers = (node->to - node->from + 1) - (node->numBuccaneers);
            updateAncestors(i);
        }
    }
}

long SegmentTree::getNumBuccaneer(long nodeIndex, long index1, long index2)
{
    Node *node = nodes.at(nodeIndex);
    if (node->from == index1 && node->to == index2)
    {
        return node->numBuccaneers;
    }
    else if (nodeIndex >= nodes.size() / 2) // leaf
    {
        return (node->numBuccaneers > 0) ? (index2 - index1 + 1) : 0;
    }
    long leftChildIndex = 2 * nodeIndex + 1;
    long rightChildIndex = 2 * nodeIndex + 2;
    Node *leftChild = nodes.at(leftChildIndex);
    Node *rightChild = nodes.at(rightChildIndex);
    if (index2 <= leftChild->to)
    {
        long left = getNumBuccaneer(leftChildIndex, index1, index2);
        return left;
    }
    else if (index1 >= rightChild->from)
    {
        long right = getNumBuccaneer(rightChildIndex, index1, index2);
        return right;
    }
    long left = getNumBuccaneer(leftChildIndex, index1, leftChild->to);
    long right = getNumBuccaneer(rightChildIndex, leftChild->to + 1, index2);
    return left + right;
}

void SegmentTree::updateAncestors(long nodeIndex)
{
    bool updatedRoot = false;
    while (!updatedRoot)
    {
        (--nodeIndex) /= 2;
        Node *current = nodes.at(nodeIndex);
        Node *left = nodes.at(2 * nodeIndex + 1);
        Node *right = nodes.at(2 * nodeIndex + 2);
        long newNumBuccaneers = left->numBuccaneers + right->numBuccaneers;
        if (current->numBuccaneers != newNumBuccaneers)
        {
            current->numBuccaneers = newNumBuccaneers;
        }
        if (nodeIndex == 0)
        {
            updatedRoot = true;
        }
    }
}

int main()
{
    int numTestCases;
    cin >> numTestCases;
    for (int i = 1; i <= numTestCases; ++i)
    {
        cout << "Case " << i << ":" << endl;
        set<long> branches;
        branches.insert(0);
        int numSets; // M ≤ 100
        cin >> numSets;
        string pirates;  // 1 ≤ N ≤ 1,024,000, 0 ~ N-1
        for (int j = 0; j < numSets; ++j)
        {
            int numRepeat;// T ≤ 200
            cin >> numRepeat;
            string pattern; // consisting of 0 and 1, 0 for Barbary, 1 for Buccaneer, has maximum length of 50
            cin >> pattern;
            for (int k = 0; k < numRepeat; ++k)
            {
                pirates += pattern;
            }
        }
        int numQueries; // 1 ≤ Q ≤ 1000
        cin >> numQueries;
        int godQueryIndex = 0;
        vector<tuple<char, long, long>> queries;
        for (int j = 0; j < numQueries; ++j)
        {
            char instruction;
            long index1, index2; // zero-based
            cin >> instruction >> index1 >> index2;
            queries.emplace_back(instruction, index1, index2);
            branches.insert(index1);
            branches.insert(index2 + 1);
        }
        SegmentTree st(pirates, branches);
        for (auto query:queries)
        {
            char instruction = get<0>(query);
            long index1 = get<1>(query);
            long index2 = get<2>(query);
            switch (instruction)
            {
                case 'F':
                    st.toBuccaneer(index1, index2);
                    break;
                case 'E':
                    st.toBarbary(index1, index2);
                    break;
                case 'I':
                    st.toInverse(index1, index2);
                    break;
                case 'S':
                    cout << "Q" << ++godQueryIndex << ": " << st.getNumBuccaneer(0, index1, index2) << endl;
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
