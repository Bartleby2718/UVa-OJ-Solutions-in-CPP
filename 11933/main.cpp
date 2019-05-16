#include <iostream>
#include <tuple>

using namespace std;

tuple<unsigned long, unsigned long> splitNumber(unsigned long nDecimal)
{// uses tail recursion, so this can be improved  
    // base case
    if (nDecimal <= 1)
    {
        return make_tuple(nDecimal, 0);
    }

    // inductive case
    unsigned long a, b;
    if (nDecimal % 2 == 0)
    {
        nDecimal /= 2;
        tie(a, b) = splitNumber(nDecimal);
        a = (a << (unsigned) 1);
    }
    else  // found 1, so swap a and b
    {
        nDecimal = nDecimal >> 1ul;
        tie(b, a) = splitNumber(nDecimal);
        ++(a <<= 1UL);
    }
    b = b * 2;
    return make_tuple(a, b);
}

int main()
{
    unsigned long nDecimal, a, b;
    cin >> nDecimal;
    while (nDecimal != 0)
    {
        tie(a, b) = splitNumber(nDecimal);
        cout << a << ' ' << b << endl;
        cin >> nDecimal;
    }
    return 0;
}
