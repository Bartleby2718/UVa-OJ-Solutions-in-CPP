/* revised after reading https://github.com/Sharknevercries/Online-Judge/blob/master/ACM-ICPC%20Live%20Archive/3619%20Sum%20of%20Different%20Primes.cpp */
#include <cstring>
#include <iostream>
#include <vector>

#define N 1120
#define K 14

using namespace std;

vector<int> primes;
int table[N + 1][K + 1];

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

void addPrimes(int n)
{
    for (int p = 2; p <= n; ++p)
    {
        if (isPrime(p))
        {
            primes.push_back(p);
        }
    }
}

void fillTable(int n, int k)
{
    memset(table, 0, sizeof(table));

    table[0][0] = 1;

    for (int prime:primes)
    {
        for (int b = n; b >= 1; --b) // sum
        {
            if (b < prime)
            {
                break;
            }
            for (int c = k; c >= 1; --c) // number of distinct primes
            {
                table[b][c] += table[b - prime][c - 1];
            }
        }
    }
}

int main()
{
    addPrimes(N);
    fillTable(N, K);
    int n, k; // n ≤ 1120, k ≤ 14
    while (cin >> n >> k, n != 0 || k != 0)
    {
        cout << table[n][k] << endl;
    }
    return 0;
}
