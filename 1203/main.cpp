#include <iostream>
#include <queue>

using namespace std;

class Query
{
    int queryId;
    int period;
    long time;
public:
    Query() = default;

    Query(int queryId, int period) : queryId(queryId), period(period)
    {
        time = period * 10000 + queryId;
    }

    int getId() const
    {
        return queryId;
    }

    long getTime() const
    {
        return time;
    }

    void addTime()
    {
        time += period * 10000;
    }
};

inline bool operator>(const Query &lhs, const Query &rhs)
{
    return lhs.getTime() > rhs.getTime();
}

int main()
{
    int queryId;  // 0 < Q_num ≤ 3000, all the queries have different Q num
    int period;  //s the interval between two consecutive returns of the result 0 < period ≤ 3000
    priority_queue<Query, vector<Query>, greater<Query>> pq;
    string instruction;  // number of the instructions will not exceed 1000
    cin >> instruction;
    while (instruction != "#")
    {
        cin >> queryId >> period;
        cin >> instruction;
        Query q(queryId, period);
        pq.push(q);
    }
    int numQueries;  // K ≤ 10000
    cin >> numQueries;
    for (int i = 0; i < numQueries; ++i)
    {
        Query q = pq.top();
        queryId = q.getId();
        cout << queryId << endl;
        pq.pop();
        q.addTime();
        pq.push(q);
    }
    return 0;
}
