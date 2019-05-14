#include <iomanip>
#include <iostream>

using namespace std;

int exponentiate(int base, int exponent)
{
    // the result must be within [-2147483648, 2147483647]
    int value = 1;
    for (int i = 0; i < exponent; ++i)
    {
        value *= base;
    }
    return value;
}

int getSplitter(int numDigits)
{
    return exponentiate(10, numDigits / 2);
}

void outputQuirksomeNumbers(int numDigits)
{
    int upperLimit = exponentiate(10, numDigits);
    int splitter = getSplitter(numDigits);
    for (int number = 0; number < upperLimit; ++number)
    {
        // only the numbers with 0,1,4,5,6,9 in the ones digit can be quirksome
        int ones = number % 10;
        if (ones != 2 && ones != 3 && ones != 7 && ones != 8)
        {
            int firstHalf = number / splitter;
            int secondHalf = number % splitter;
            int sum = firstHalf + secondHalf;
            if (sum * sum == number)
            {
                cout << setfill('0') << setw(numDigits / 2) << firstHalf;
                cout << setfill('0') << setw(numDigits / 2) << secondHalf << endl;
            }
        }
    }
}

int main()
{
    int numDigits;
    while (cin >> numDigits)
    {
        outputQuirksomeNumbers(numDigits);
    }
    return 0;
}
