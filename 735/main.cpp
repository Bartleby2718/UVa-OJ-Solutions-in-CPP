#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

const vector<int> possibleScores()
{
    vector<int> scores(50);
    for (int i = 1; i <= 20; ++i)
    {
        for (int j = 1; j <= 3; ++j)
        {
            int product = i * j;
            bool notFound = find(scores.begin(), scores.end(), product) == scores.end();
            if (notFound)
            {
                scores.push_back(product);
            }
        }
    }
    scores.push_back(0);
    scores.push_back(50);
    scores.erase(unique(scores.begin(), scores.end()), scores.end());
    return scores;
}

tuple<bool, int, int> get(int score, const vector<int> &scores)
{
    // enforce i >= j >= k and count how many of them are identical
    int numCombinations = 0;
    int numPermutations = 0;
    for (int i = min(score, 60); i >= (score + 2) / 3; --i)
    {
        if (find(scores.begin(), scores.end(), i) == scores.end())
        {
            continue;
        }
        for (int j = min(i, 60); j >= (score - i + 1) / 2; --j)
        {
            if (find(scores.begin(), scores.end(), j) == scores.end())
            {
                continue;
            }
            int k = score - i - j;
            if (find(scores.begin(), scores.end(), k) == scores.end() || k > j)
            {
                continue;
            }
            ++numCombinations;
            vector<int> v = {i, j, k};
            int numUnique = unique(v.begin(), v.end()) - v.begin();
            numPermutations += (numUnique == 1) ? 1 : (numUnique == 2) ? 3 : 6;
        }
    }
    bool found = numCombinations != 0;
    return make_tuple(found, numCombinations, numPermutations);
}

void printOutput(int score, bool possible, int c, int p)
{
    if (possible)
    {
        printf("NUMBER OF COMBINATIONS THAT SCORES %d IS %d.\n", score, c);
        printf("NUMBER OF PERMUTATIONS THAT SCORES %d IS %d.\n", score, p);
    }
    else
    {
        printf("THE SCORE OF %d CANNOT BE MADE WITH THREE DARTS.\n", score);
    }
}

int main()
{
    const vector<int> scores = possibleScores();
    int score; // each ≤ 999
    cin >> score;
    while (score > 0)
    {
        bool possible;
        int numCombinations, numPermutations;
        tie(possible, numCombinations, numPermutations) = get(score, scores);
        printOutput(score, possible, numCombinations, numPermutations);
        cout << string(70, '*') << std::endl;
        cin >> score;
    }
    cout << "END OF OUTPUT\n";
    return 0;
}
