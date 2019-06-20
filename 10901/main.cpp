#include <iostream>
#include <limits>
#include <queue>
#include <vector>

using namespace std;

struct Car
{
public:
    int bankArrivalTime;
    int timeCrossed;

    explicit Car(int bankArrivalTime)
            : bankArrivalTime(bankArrivalTime), timeCrossed(0)
    {
    }
};

class Bank
{
    bool onLeft;
    queue<Car *> cars;
public:
    Bank(queue<Car *> cars, bool onLeft);

    bool hasCars() const;

    bool hasCarsWaiting(int currentTime) const;

    Car *takeOutFirstCar();

    Car *nextCarArriving() const;
};

Bank::Bank(queue<Car *> cars, bool onLeft)
        : cars(move(cars)), onLeft(onLeft)
{
}

bool Bank::hasCars() const
{
    return !cars.empty();
}

bool Bank::hasCarsWaiting(int currentTime) const
{
    return hasCars() && cars.front()->bankArrivalTime <= currentTime;
}

Car *Bank::takeOutFirstCar()
{
    Car *car = cars.front();
    cars.pop();
    return car;
}

Car *Bank::nextCarArriving() const
{
    return cars.front();
}

class Ferry
{
    Bank &thisBank;
    Bank &otherBank;
    int capacity;
    int timeToCross;
    int numCars;
    int currentTime;
    bool onLeft;
    queue<Car *> cars;

    bool hasSpace() const;

public:
    Ferry(Bank &leftBank, Bank &rightBank, int capacity, int timeToCross, int numCars);

    bool isOver() const;

    void load();

    void cross();

    void unload();
};

bool Ferry::isOver() const
{
    return !thisBank.hasCars() && !otherBank.hasCars();
}

void Ferry::load()
{
    bool readyToCross = false;
    while (!readyToCross)
    {
        if (thisBank.hasCarsWaiting(currentTime))
        { // Case 1: cars waiting
            while (hasSpace() && thisBank.hasCarsWaiting(currentTime))
            {
                Car *car = thisBank.takeOutFirstCar();
                cars.push(car);
                readyToCross = true;
            }
        }
        else if (otherBank.hasCarsWaiting(currentTime))
        { // Case 2: no cars waiting but cars waiting on the other sie
            readyToCross = true;
        }
        else
        { // Case 3: no cars waiting on both sides
            int nextTimeFrame = numeric_limits<int>::max();
            if (thisBank.hasCars())
            {
                int thisBankNextCar = thisBank.nextCarArriving()->bankArrivalTime;
                if (thisBankNextCar < nextTimeFrame)
                {
                    nextTimeFrame = thisBankNextCar;
                }
            }
            if (otherBank.hasCars())
            {
                int otherBankNextCar = otherBank.nextCarArriving()->bankArrivalTime;
                if (otherBankNextCar < nextTimeFrame)
                {
                    nextTimeFrame = otherBankNextCar;
                    readyToCross = true;
                }
            }
            currentTime = nextTimeFrame;
        }
    }
}

void Ferry::cross()
{
    currentTime += timeToCross;
    onLeft = !onLeft;
    swap(thisBank, otherBank);
}

void Ferry::unload()
{
    while (!cars.empty())
    {
        Car *car = cars.front();
        car->timeCrossed = currentTime;
        cars.pop();
    }
}

Ferry::Ferry(Bank &leftBank, Bank &rightBank, int capacity, int timeToCross, int numCars)
        : thisBank(leftBank), otherBank(rightBank), capacity(capacity), timeToCross(timeToCross), numCars(numCars)
{
    currentTime = 0;
    onLeft = true;
}

bool Ferry::hasSpace() const
{
    return cars.size() < capacity;
}

int main()
{
    int numTestCases; // c
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; ++i)
    {
        if (i != 0) // Output an empty line between cases
        {
            cout << endl;
        }
        int capacity, timeToCross, numCars; // 0 < n, t, m ≤ 10000
        cin >> capacity >> timeToCross >> numCars;
        queue<Car *> leftCars, rightCars;
        vector<Car *> allCars;
        allCars.reserve(numCars);
        for (int j = 0; j < numCars; ++j)
        {
            int arrivalTime;
            string where;
            cin >> arrivalTime >> where;
            auto car = new Car(arrivalTime);
            allCars.push_back(car);
            if (where == "left")
            {
                leftCars.push(car);
            }
            else if (where == "right")
            {
                rightCars.push(car);
            }
        }
        Bank leftBank(leftCars, true), rightBank(rightCars, false);
        Ferry ferry(leftBank, rightBank, capacity, timeToCross, numCars);
        while (!ferry.isOver())
        {
            ferry.load();
            ferry.cross();
            ferry.unload();
        }
        for (Car *car:allCars)
        {
            cout << car->timeCrossed << endl;
        }
    }
    return 0;
}
