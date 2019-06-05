#include <iostream>

using namespace std;

bool checkAllSame(string &zerosAndOnes, long index1, long index2)
{
    long smaller = index1 <= index2 ? index1 : index2;
    long bigger = index1 >= index2 ? index1 : index2;
    char firstDigit = zerosAndOnes.at(smaller);
    for (long j = smaller + 1; j <= bigger; ++j)
    {
        char digit = zerosAndOnes.at(j);
        if (digit != firstDigit)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    string zerosAndOnes;
    int index = 0;
    while (cin >> zerosAndOnes)
    {
        cout << "Case " << ++index << ":" << endl;
        int numQueries;
        cin >> numQueries;
        for (int i = 1; i <= numQueries; ++i)
        {
            long index1, index2;
            cin >> index1 >> index2;
            bool allSame = checkAllSame(zerosAndOnes, index1, index2);
            cout << (allSame ? "Yes" : "No") << endl;
        }
    }
    return 0;
}
