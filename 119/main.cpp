#include <iostream>
#include <map>

int main()
{
    int numPeople; // no more than 10
    bool isFirst = true;
    while (std::cin >> numPeople)
    {
        // blank line between groups
        if (isFirst)
        {
            isFirst = false;
        }
        else
        {
            std::cout << std::endl;
        }

        int total, each; // nonnegative integer less than 2000
        std::string giver, receiver; // all lowercase, no more than 12 characters
        int numReceivers;
        std::string names[numPeople];
        std::map<std::string, int> balance;
        for (int i = 0; i < numPeople; ++i)
        {
            std::cin >> giver;
            names[i] = giver;
            balance.insert(std::make_pair(giver, 0));
        }
        for (int i = 0; i < numPeople; ++i)
        {
            std::cin >> giver >> total >> numReceivers;
            if (numReceivers != 0)
            {
                each = total / numReceivers;
                balance[giver] -= each * numReceivers;
                for (int j = 0; j < numReceivers; ++j)
                {
                    std::cin >> receiver;
                    balance[receiver] += each;
                }
            }
        }
        for (auto &name:names)
        {
            total = balance[name];
            std::cout << name << ' ' << total << std::endl;
        }
    }
    return 0;
}
