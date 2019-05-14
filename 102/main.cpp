#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    char colors[3] = {'B', 'C', 'G'};  /* changed order for alphabetical order*/
    long bin1[3], bin2[3], bin3[3];
    while (cin >> bin1[0] >> bin1[2] >> bin1[1] >> bin2[0] >> bin2[2] >> bin2[1] >> bin3[0] >> bin3[2] >> bin3[1])
    {  /* Note: changed order above for alphabetical order*/
        int indices[3] = {0, 1, 2};  /* all possible indices */
        int maxIndices[3] = {0, 1, 2};  /* indices of colors to fix for each bin*/
        long max = 0;
        do
        {
            long sum = bin1[indices[0]] + bin2[indices[1]] + bin3[indices[2]];
            if (sum > max)
            {
                max = sum;
                copy(begin(indices), end(indices), begin(maxIndices));
            }
        } while (next_permutation(indices, indices + 3));
        long sum1 = accumulate(begin(bin1), end(bin1), 0, plus<long>());
        long sum2 = accumulate(begin(bin2), end(bin2), 0, plus<long>());
        long sum3 = accumulate(begin(bin3), end(bin3), 0, plus<long>());
        long sumFixed = bin1[maxIndices[0]] + bin2[maxIndices[1]] + bin3[maxIndices[2]];
        long sumMoved = sum1 + sum2 + sum3 - sumFixed;
        cout << colors[maxIndices[0]] << colors[maxIndices[1]] << colors[maxIndices[2]] << ' ' << sumMoved << endl;
    }
    return 0;
}
