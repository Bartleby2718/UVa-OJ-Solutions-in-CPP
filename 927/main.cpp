#include <iostream>
#include <vector>

using namespace std;

long long calculatePolynomial(vector<int> &coefficients, int n)
{
    long long value = 0;
    for (auto i = coefficients.rbegin(); i != coefficients.rend(); ++i)
    {
        int coefficient = *i;
        value = (value * n) + coefficient;
    }
    return value;
}

int findN(long numOccurrences, long oneBasedIndex)
{
    for (int i = 1;; ++i)
    {
        // between two triangular numbers
        if (numOccurrences * i * (i - 1) / 2 < oneBasedIndex && oneBasedIndex <= numOccurrences * i * (i + 1) / 2)
        {
            return i;
        }
    }
}

long long getNumber(vector<int> coefficients, long numOccurrences, long oneBasedIndex)
{
    int n = findN(numOccurrences, oneBasedIndex);
    long long value = calculatePolynomial(coefficients, n);
    return value;
}

int main()
{
    int numTestCases;  // 0 < C < 100)
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; ++i)
    {
        int degree;  // degree of polynomial (1 ≤ i ≤ 20)
        cin >> degree;
        vector<int> coefficients(degree + 1);  // 0 ≤ cj ≤ 10000, j = 0, . . . , i)
        for (int k = 0; k < degree + 1; ++k)
        {
            cin >> coefficients.at(k);
        }
        long numOccurrences; // 1 ≤ d ≤ 100000
        cin >> numOccurrences;
        long oneBasedIndex; // 1 ≤ k ≤ 1000000.
        cin >> oneBasedIndex;
        long long number = getNumber(coefficients, numOccurrences, oneBasedIndex);
        cout << number << endl;
    }
    return 0;
}
