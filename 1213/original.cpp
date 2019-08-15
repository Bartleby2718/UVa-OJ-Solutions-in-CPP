/* time limit because of the inefficient bottom-up approach with an extra loop*/
#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int n)
{
    if (n < 2)
    {
        return false;
    }
    for (int p = 2; p * p <= n; ++p)
    {
        if (n % p == 0)
        {
            return false;
        }
    }
    return true;
}

vector<int> getPrimesLessThanOrEqualToN(int n)
{
    vector<int> primes;
    for (int p = 2; p <= n; ++p)
    {
        if (isPrime(p))
        {
            primes.push_back(p);
        }
    }
    return primes;
}

long getNumWays(int n, int k)
{
    vector<int> primes = getPrimesLessThanOrEqualToN(n);
    int numPrimes = primes.size();

    long*** table = new long** [numPrimes + 1];
    for (int i = 0; i < numPrimes + 1; ++i)
    {
        table[i] = new long* [n + 1];
        for (int j = 0; j < n + 1; ++j)
        {
            table[i][j] = new long[k + 1]();
        }
    }
    // 0 primes
    table[0][0][0] = 1;

    // 1 prime
    for (int i = 1; i <= numPrimes; ++i)
    {
        int prime = primes.at(i - 1);
        table[i][prime][1] = 1;
    }

    // 2+ primes
    for (int a = 2; a <= numPrimes; ++a) // one-based index of primes
    {
        int prime = primes.at(a - 1);
        for (int b = prime + 2; b <= n; ++b) // sum
        {
            for (int c = 2; c <= k; ++c) // number of distinct primes
            {
                long numWays = 0;
                for (int i = 1; i < a; ++i)
                {
                    numWays += table[i][b - prime][c - 1];
                }
                table[a][b][c] = numWays;
                // if (numWays != 0)
                // {
                //     cout << "table[" << a << "][" << b << "][" << c << "] = " << numWays << endl;
                // }
            }
        }
    }

    long numWays = 0;
    for (int p = 0; p <= numPrimes; ++p)
    {
        numWays += table[p][n][k];
    }
    return numWays;
}

int main()
{
    int n, k; // n ≤ 1120, k ≤ 14
    while (cin >> n >> k, n != 0 || k != 0)
    {
        long numWays = getNumWays(n, k); // less than 2^31
        cout << numWays << endl;
    }
    return 0;
}
