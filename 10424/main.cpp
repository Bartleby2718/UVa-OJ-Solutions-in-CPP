#include <iomanip>
#include <iostream>

using namespace std;

double getRatio(string &name1, string &name2)
{

    int sum1 = 0;
    for (char c:name1)
    {
        if (isalpha(c))
        {
            int value = toupper(c) - 'A' + 1;
            sum1 += value;
        }
    }
    sum1 = (sum1 - 1) % 9 + 1;

    int sum2 = 0;
    for (char c :name2)
    {
        if (isalpha(c))
        {
            int value = toupper(c) - 'A' + 1;
            sum2 += value;
        }
    }
    sum2 = (sum2 - 1) % 9 + 1;

    double ratio = (sum1 <= sum2) ? (sum1 / double(sum2)) : (sum2 / double(sum1));
    return ratio;
}

int main()
{
    string name1, name2; // no more than 25 characters
    while (cin.peek() != EOF)
    {
        getline(cin, name1);
        getline(cin, name2);
        double ratio = getRatio(name1, name2);
        cout << fixed << setprecision(2) << ratio * 100 << " %" << endl;
    }
    return 0;
}
