#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Carrier
{
    int time;
    int numStations;
    int stackCapacity;
    int queueCapacity;
    int currentStation;
    int remainingCargoes;
    vector<queue<int>> platformBs;
    vector<int> cargoes;

    queue<int> &getCargoesInCurrentStation();

    void moveToNextPlatform();

    void unload();

    void load();

public:
    Carrier(int numStations, int stackCapacity, int queueCapacity, const vector<queue<int>> &platformBs);

    int calculate();
};

Carrier::Carrier(int numStations, int stackCapacity, int queueCapacity, const vector<queue<int>> &platformBs)
        : numStations(numStations), stackCapacity(stackCapacity), queueCapacity(queueCapacity), platformBs(platformBs)
{
    time = 0;
    currentStation = 0;
    remainingCargoes = 0;
    for (auto &platformB:platformBs)
    {
        remainingCargoes += platformB.size();
    }
}

queue<int> &Carrier::getCargoesInCurrentStation()
{
    return platformBs[currentStation];
}

void Carrier::moveToNextPlatform()
{
    (++currentStation) %= numStations;
    time += 2;
}

void Carrier::unload()
{
    while (!cargoes.empty() &&
           (cargoes.back() == currentStation || getCargoesInCurrentStation().size() < queueCapacity))
    {
        if (cargoes.back() == currentStation) // unload to platform A
        {
            cargoes.pop_back();
            --remainingCargoes;
        }
        else  // unload to platform B
        {
            int topCargo = cargoes.back();
            cargoes.pop_back();
            queue<int> &cargoesInStation = getCargoesInCurrentStation();
            cargoesInStation.push(topCargo);
        }
        ++time;
    }
}

void Carrier::load()
{
    while (cargoes.size() < stackCapacity && !getCargoesInCurrentStation().empty())
    {
        queue<int> &cargoesInStation = getCargoesInCurrentStation();
        int firstCargo = cargoesInStation.front();
        cargoesInStation.pop();
        cargoes.push_back(firstCargo);
        ++time;
    }
}

int Carrier::calculate()
{
    load(); // initially at Station 1 with empty cargo
    while (remainingCargoes != 0)
    {
        moveToNextPlatform();
        unload();
        load();
    }
    return time;
}

int main()
{
    int numSets;
    cin >> numSets;
    for (int i = 0; i < numSets; ++i)
    {
        int numStations; // 2 ≤ N ≤ 100
        int stackCapacity; // 1 ≤ S ≤ 100
        int queueCapacity; // 1 ≤ Q ≤ 100
        cin >> numStations >> stackCapacity >> queueCapacity;
        vector<queue<int>> platformBs(numStations);
        for (auto &platform:platformBs)
        {
            int numCargoes;
            cin >> numCargoes; // 0 ≤ Q_i ≤ Q
            for (int k = 0; k < numCargoes; ++k)
            {
                int cargo;
                cin >> cargo; // one-based
                platform.push(--cargo); // make zero-based
            }
        }
        Carrier c(numStations, stackCapacity, queueCapacity, platformBs);
        int timeRequired = c.calculate();
        cout << timeRequired << endl;
    }
    return 0;
}
