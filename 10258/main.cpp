#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Contestant
{
    unsigned numProblemSolved;
    unsigned penaltyTime;
    const unsigned teamNumber;
    vector<bool> problemSolved;
    vector<unsigned> savedPenalties;
public:
    explicit Contestant(unsigned teamNumber)
            : numProblemSolved(0), penaltyTime(0), teamNumber(teamNumber)
    {
        problemSolved.resize(9);
        savedPenalties.resize(9);
    }

    void gotCorrect(unsigned problemId, unsigned timeTaken);

    void gotWrong(unsigned problemId);

    bool hasSolved(unsigned problemId) const;

    void displayStats() const;

    friend struct ContestantPointerLessThan;
};

struct ContestantPointerLessThan
{
    bool const operator()(const Contestant *lhs, const Contestant *rhs) const
    {
        if (lhs == nullptr)
        {
            return false;
        }
        if (rhs == nullptr)
        {
            return true;
        }
        if (lhs->numProblemSolved != rhs->numProblemSolved)
        {
            return lhs->numProblemSolved >= rhs->numProblemSolved;
        }
        if (lhs->penaltyTime != rhs->penaltyTime)
        {
            return lhs->penaltyTime <= rhs->penaltyTime;
        }
        return lhs->teamNumber < rhs->teamNumber;
    }
};

bool Contestant::hasSolved(unsigned problemId) const
{
    return problemSolved[problemId - 1];
}

void Contestant::displayStats() const
{
    cout << teamNumber << ' ' << numProblemSolved << ' ' << penaltyTime << endl;
}

void Contestant::gotCorrect(unsigned problemId, unsigned timeTaken)
{
    problemSolved[problemId - 1] = true;
    penaltyTime += savedPenalties[problemId - 1] + timeTaken;
    ++numProblemSolved;
}

void Contestant::gotWrong(unsigned problemId)
{
    savedPenalties[problemId - 1] += 20;
}

struct Submission
{
    unsigned contestant;
    unsigned problem;
    unsigned time;
    char letter;

    Submission(unsigned contestant, unsigned problem, unsigned time, char letter)
            : contestant(contestant), problem(problem), time(time), letter(letter)
    {
    }
};

class Board
{
    vector<Contestant *> contestants;
public:
    Board();

    void process(const Submission &submission);

    void sortContestants();

    void display() const;
};

void Board::process(const Submission &submission)
{
    if (contestants[submission.contestant - 1] == nullptr)
    {
        contestants[submission.contestant - 1] = new Contestant(submission.contestant);
    }
    // not null
    Contestant *contestant = contestants[submission.contestant - 1];

    if (contestant->hasSolved(submission.problem))
    {
        return;
    }

    // unsolved problems only
    if (submission.letter == 'C')
    {
        contestant->gotCorrect(submission.problem, submission.time);
    }
    else if (submission.letter == 'I')
    {
        contestant->gotWrong(submission.problem);
    }
}

void Board::display() const
{
    for (Contestant *contestant:contestants)
    {
        if (contestant != nullptr)
        {
            contestant->displayStats();
        }
    }
}

Board::Board()
{
    contestants.resize(100);
}

void Board::sortContestants()
{
    sort(contestants.begin(), contestants.end(), ContestantPointerLessThan());
}

int main()
{
    int numCases; // a positive integer
    cin >> numCases;
    getchar(), getchar(); // consume newline characters
    for (int i = 0; i < numCases; ++i)
    {
        if (i != 0)
        {
            cout << endl;  // blank line between consecutive cases
        }

        Board board;
        int contestant;  // 1~100
        int problem;  // 1~9
        int time;
        char letter;  // one of 'C', 'I', 'R', 'U', 'E'
        string line;
        while (getline(cin, line), !line.empty())
        {
            stringstream ss(line);
            ss >> contestant >> problem >> time >> letter;
            Submission submission(contestant, problem, time, letter);
            board.process(submission);
        }
        board.sortContestants();
        board.display();
    }
    return 0;
}
