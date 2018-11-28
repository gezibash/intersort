#ifndef INTERSORT_DISTRIBUTIONS_H
#define INTERSORT_DISTRIBUTIONS_H

#include "Helpers.h"

namespace Intersort
{
    template<typename T>
    T randNumber(int low, int high)
    {
        std::mt19937 randomSeed;
        randomSeed.seed(std::random_device()());
        std::uniform_real_distribution<T> tempDist(low, high);
        return tempDist(randomSeed);
    }

    template<>
    int randNumber(int low, int high)
    {
        std::mt19937 randomSeed;
        randomSeed.seed(std::random_device()());
        std::uniform_int_distribution<int> tempDist(low, high);
        return tempDist(randomSeed);
    }

    template<typename T>
    std::vector<T> uniformDistribution(int len, int low, int high)
    {
        std::mt19937 randomSeed;
        randomSeed.seed(std::random_device()());
        std::uniform_real_distribution<T> tempDist(low, high);

        std::vector<T> numbers;
        for(int i = 0; i < len; i++)
            numbers.push_back(tempDist(randomSeed));

        return numbers;
    }

    template<>
    std::vector<int> uniformDistribution(int len, int low, int high)
    {
        std::mt19937 randomSeed;
        randomSeed.seed(std::random_device()());
        std::uniform_int_distribution<int> tempDist(low, high);

        std::vector<int> numbers;
        for(int i = 0; i < len; i++)
            numbers.push_back(tempDist(randomSeed));

        return numbers;
    }

    template<typename T>
    std::vector<int> poissonDistribution(int len, T mean)
    {
        std::mt19937 randomSeed;
        randomSeed.seed(std::random_device()());
        std::poisson_distribution<int> tempDist(mean);

        std::vector<int> numbers;
        for(int i = 0; i < len; i++)
            numbers.push_back(tempDist(randomSeed));

        return numbers;
    }

    template<typename T>
    std::vector<T> exponentialDistribution(int len, T m)
    {
        std::mt19937 randomSeed;
        randomSeed.seed(std::random_device()());
        std::exponential_distribution<T> dist(m);

        std::vector<T> numbers;
        for(int i = 0; i < len; i++)
            numbers.push_back(dist(randomSeed));

        return numbers;
    }

    template<typename T>
    std::vector<T> normalDistribution(int len, T m, T s)
    {
        std::mt19937 randomSeed;
        randomSeed.seed(std::random_device()());
        std::normal_distribution<T> normalDist(m, s);

        std::vector<T> numbers;
        for(int i = 0; i < len; i++)
            numbers.push_back(normalDist(randomSeed));

        return numbers;
    }
}

#endif