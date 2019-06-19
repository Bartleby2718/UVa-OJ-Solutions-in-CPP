#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    long m, n; // each at most one million
    cin >> n >> m;
    while (n != 0 || m != 0)
    {
        vector<long> jack(n), jill(m);
        for (long i = 0; i < n; ++i)
        {
            cin >> jack[i];  // a positive integer no greater than one billion
        }
        for (long i = 0; i < m; ++i)
        {
            cin >> jill[i];  // a positive integer no greater than one billion
        }
        long count = 0;
        for (long value:jack)
        {
            if (binary_search(jill.begin(), jill.end(), value))
            {
                ++count;
            }
        }
        cout << count << endl;
        cin >> n >> m;
    }
    return 0;
}
