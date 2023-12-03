#include "Func.h"

std::map<int, int> getStacksOfCards(Deck& deck, int n)
{
    int count = 0;
    std::map<int, int> stacks;
    Card lastCard{ -1, 0 }, currCard;
    for (int i = 0; i != n; ++i) {
        currCard = deck();
        if (lastCard >= currCard)
        {
            ++stacks[count];
            count = 0;
        }
        ++count;
        lastCard = currCard;
    }
    ++stacks[count];
    return stacks;
}

std::map<int, double> inPercentage(const std::map<int, int>& stacks) {
    int count = 0;
    for (const auto& x : stacks)
        count += x.second;
    std::map<int, double> result;
    for (const auto& x : stacks)
        result[x.first] = (double)x.second / count * 100;
    return result;
}

std::vector<int> frequent(const std::map<int, int>& stacks) {
    int frequency = 0;
    for (const auto& x : stacks)
        frequency = x.second > frequency ? x.second : frequency;
    std::vector<int> result;
    for (const auto& x : stacks)
        if (frequency == x.second)
            result.push_back(x.first);
    return result;
}


double average(const std::map<int, int>& stacks) {
    int a = 0, b = 0;
    for (const auto& x : stacks) {
        a += x.first * x.second;
        b += x.second;
    }
    return (double)a / b;
}

double median(const std::map<int, int>& stacks) {
    int count = 0, mid = 0;
    for (const auto& x : stacks)
        count += x.second;
    for (auto it = stacks.begin(); it != stacks.end(); ++it) {
        mid += it->second;
        if (mid*2 >= count)
            if ((count & 1) == 0 && mid == count / 2)
                return (double)(it->first + (++it)->first) / 2;   //works correctly only with C++20 standart
            else 
                return it->first;
    }
}