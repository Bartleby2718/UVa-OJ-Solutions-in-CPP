#include <iostream>
#include <tuple>

using namespace std;

char *getReverse(char c)
{
    char *p = new char[1];
    switch (c)
    {
        case 'A':
            *p = 'A';
            break;
        case 'E':
            *p = '3';
            break;
        case 'H':
            *p = 'H';
            break;
        case 'I':
            *p = 'I';
            break;
        case 'J':
            *p = 'L';
            break;
        case 'L':
            *p = 'J';
            break;
        case 'M':
            *p = 'M';
            break;
        case 'O':
            *p = 'O';
            break;
        case 'S':
            *p = '2';
            break;
        case 'T':
            *p = 'T';
            break;
        case 'U':
            *p = 'U';
            break;
        case 'V':
            *p = 'V';
            break;
        case 'W':
            *p = 'W';
            break;
        case 'X':
            *p = 'X';
            break;
        case 'Y':
            *p = 'Y';
            break;
        case 'Z':
            *p = '5';
            break;
        case '1':
            *p = '1';
            break;
        case '2':
            *p = 'S';
            break;
        case '3':
            *p = 'E';
            break;
        case '5':
            *p = 'Z';
            break;
        case '8':
            *p = '8';
            break;
        default:
            delete[] p;
            p = nullptr;
    }
    return p;
}

tuple<bool, bool> determine(string &input)
{
    bool isPalindrome = true, isMirrored = true;
    int length = input.size();
    int midIndex = (length - 1) / 2;
    for (int i = 0; (i < midIndex + 1) && (isPalindrome || isMirrored); ++i)
    {
        char c = input.at(i);
        char opposite = input.at(length - 1 - i);
        if (isPalindrome)
        {
            isPalindrome = c == opposite;
        }
        if (isMirrored)
        {
            char *pReverse = getReverse(c);
            isMirrored = (pReverse != nullptr) && (*pReverse == opposite); // short circuiting
        }
    }
    return make_tuple(isPalindrome, isMirrored);
}

string getOutput(bool isPalindrome, bool isMirrored)
{
    if (!isPalindrome && !isMirrored)
    {
        return " -- is not a palindrome.";
    }
    else if (isPalindrome && !isMirrored)
    {
        return " -- is a regular palindrome.";
    }
    else if (!isPalindrome && isMirrored)
    {
        return " -- is a mirrored string.";
    }
    else // isPalindrome && isMirrored
    {
        return " -- is a mirrored palindrome.";
    }
}

void testDetermine(string &input, bool expectedIsPalindrome, bool expectedIsMirrored)
{
    bool actualIsPalindrome, actualIsMirrored;
    tie(actualIsPalindrome, actualIsMirrored) = determine(input);
    cout << input << endl;
    cout << "isPalindrome - expected " << expectedIsPalindrome << " got " << actualIsPalindrome << endl;
    cout << "isMirrored - expected " << expectedIsMirrored << " got " << actualIsMirrored << endl;
}

int main()
{
    string input1 = "NOTAPALINDROME";
    testDetermine(input1, false, false);
    string input2 = "ISAPALINILAPASI";
    testDetermine(input2, true, false);
    string input3 = "2A3MEAS";
    testDetermine(input3, false, true);
    string input4 = "ATOYOTA";
    testDetermine(input4, true, true);

    string input; // one to twenty valid characters
    while (cin >> input)
    {
        bool isPalindrome;
        bool isMirrored;
        tie(isPalindrome, isMirrored) = determine(input);
        string output = getOutput(isPalindrome, isMirrored);
        cout << input << output << endl << endl;
    }
    return 0;
}
