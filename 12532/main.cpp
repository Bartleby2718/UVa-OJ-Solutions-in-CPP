#include <iostream>
#include <vector>

using namespace std;

class Node
{
    long from;
    long to;
    int sign; // 1 if positive, -1 if negative, 0 otherwise
public:
    Node(long from, long to, int signedInt);

    friend class SegmentTree;
};

class SegmentTree
{
    vector<Node *> nodes;

public:
    explicit SegmentTree(const vector<int> &values);

    bool isLeafIndex(long nodeIndex);

    void update(long valueIndex, int newValue);

    int getProductSign(long nodeIndex, long from, long to);
};

long greatestPowerOfTwo(long upperLimit)
{
    long value = 0;
    while (value < upperLimit)
    {
        value = 2 * value + 1;
    }
    return value / 2;
}

Node::Node(long from, long to, int signedInt)
        : from(from), to(to), sign(signedInt)
{
}

bool SegmentTree::isLeafIndex(long nodeIndex)
{
    return (nodes.size() / 2 <= nodeIndex) && (nodeIndex < nodes.size());
}

SegmentTree::SegmentTree(const vector<int> &values)
{
    // Step 1: fill leaves
    long numLeafNodes = values.size();
    long firstLeafIndex = numLeafNodes - 1;
    long numNodes = 2 * numLeafNodes - 1;
    nodes.resize(numNodes);
    for (long i = 0, nodeIndex = greatestPowerOfTwo(numNodes); i < numLeafNodes; ++i, ++nodeIndex)
    {
        if (nodeIndex == numNodes)
        {
            nodeIndex = firstLeafIndex;
        }
        int value = values.at(i);
        int signedInt = (value > 0) ? 1 : ((value < 0) ? -1 : 0);
        nodes.at(nodeIndex) = new Node(i, i, signedInt);
    }
    // Step 2: fill internal nodes
    for (long i = nodes.size() / 2 - 1; i >= 0; --i)
    {
        Node *left = nodes.at(2 * i + 1);
        Node *right = nodes.at(2 * i + 2);
        nodes.at(i) = new Node(left->from, right->to, left->sign * right->sign);
    }
}

void SegmentTree::update(long valueIndex, int newValue)
{
    long nodeIndex = greatestPowerOfTwo(nodes.size()) + valueIndex;
    if (nodeIndex >= nodes.size())
    {
        nodeIndex -= (nodes.size() / 2 + 1);
    }
    // Use one-based index i, just for this method
    for (long i = nodeIndex + 1; i > 0; i /= 2)
    {
        Node *node = nodes.at(i - 1);
        int originalSign = node->sign;
        int newSign = (newValue > 0) ? 1 : ((newValue < 0) ? -1 : 0);
        if (!isLeafIndex(i - 1))
        {
            Node *left = nodes.at(2 * i - 1);
            Node *right = nodes.at(2 * i);
            newSign = left->sign * right->sign;
        }
        if (originalSign == newSign)
        {
            break;
        }
        else
        {
            node->sign = newSign;
        }
    }
}

int SegmentTree::getProductSign(long nodeIndex, long from, long to)
{
    Node *node = nodes.at(nodeIndex);
    if (from == node->from && to == node->to)
    {
        return node->sign;
    }
    else
    {
        long leftIndex = 2 * nodeIndex + 1;
        long rightIndex = 2 * nodeIndex + 2;
        Node *left = nodes.at(leftIndex);
        Node *right = nodes.at(rightIndex);
        if (to <= left->to)
        {
            return getProductSign(leftIndex, from, to);
        }
        else if (from >= right->from)
        {
            return getProductSign(rightIndex, from, to);
        }
        else
        {
            int leftSign = getProductSign(leftIndex, from, left->to);
            int rightSign = getProductSign(rightIndex, right->from, to);
            return leftSign * rightSign;
        }
    }
}

char intToSign(int signedInt)
{
    switch (signedInt)
    {
        case 1:
            return '+';
        case 0:
            return '0';
        case -1:
            return '-';
        default:
            return '?';
    }
}

int main()
{
    long numValues; // N
    long numRounds; // K
    while (cin >> numValues >> numRounds)
    {
        vector<int> values(numValues);
        for (long i = 0; i < numValues; ++i)
        {
            cin >> values.at(i);
        }
        SegmentTree st(values);
        char command;
        long index, from, to; // all zero-based
        int value;
        for (long i = 0; i < numRounds; ++i)
        {
            cin >> command;
            if (command == 'C')
            {
                cin >> index >> value;
                --index; // make zero-based
                st.update(index, value);
            }
            else if (command == 'P')
            {
                cin >> from >> to;
                --from, --to; // make zero-based
                int signedInt = st.getProductSign(0, from, to);
                char sign = intToSign(signedInt);
                cout << sign;
            }
        }
        cout << endl;
    }
    return 0;
}
