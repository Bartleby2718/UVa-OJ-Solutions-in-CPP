#include <iostream>
#include <vector>

using namespace std;

long getMaximumGain(const vector<int> &sequence)
{
    int numBets = sequence.size();
    vector<long> maxSums;
    maxSums.reserve(numBets);
    int answer = sequence[0];
    maxSums.push_back(answer);
    for (int i = 1; i < numBets; ++i)
    {
        int bet = sequence[i];
        long currentMax = maxSums[i - 1];
        long maxSum = max(currentMax, 0L) + bet;
        maxSums.push_back(maxSum);
        if (maxSum > answer)
        {
            answer = maxSum;
        }
    }
    return answer;
}

int main()
{
    int length; // N ≤ 10000
    while (cin >> length, length != 0)
    {
        vector<int> sequence;
        sequence.reserve(length);
        for (int i = 0; i < length; ++i)
        {
            int bet; // nonzero and absolute value less than 1000
            cin >> bet;
            sequence.push_back(bet);
        }
        long maximumGain = getMaximumGain(sequence);
        if (maximumGain > 0)
        {
            cout << "The maximum winning streak is " << maximumGain << "." << endl;
        }
        else
        {
            cout << "Losing streak." << endl;
        }
    }
    return 0;
}
