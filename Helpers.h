#ifndef INTERSORT_HELPERS
#define INTERSORT_HELPERS

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

namespace Intersort {

    void printWelcomeScreen()
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;  
        std::cout << " ██╗███╗   ██╗████████╗███████╗██████╗ ███████╗ ██████╗ ██████╗ ████████╗\n";
        std::cout << " ██║████╗  ██║╚══██╔══╝██╔════╝██╔══██╗██╔════╝██╔═══██╗██╔══██╗╚══██╔══╝\n";
        std::cout << " ██║██╔██╗ ██║   ██║   █████╗  ██████╔╝███████╗██║   ██║██████╔╝   ██║\n";   
        std::cout << " ██║██║╚██╗██║   ██║   ██╔══╝  ██╔══██╗╚════██║██║   ██║██╔══██╗   ██║ \n";  
        std::cout << " ██║██║ ╚████║   ██║   ███████╗██║  ██║███████║╚██████╔╝██║  ██║   ██║ \n";  
        std::cout << " ╚═╝╚═╝  ╚═══╝   ╚═╝   ╚══════╝╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═╝  ╚═╝   ╚═╝\n";   
        std::cout << "-------------------------------------------------------------------------" << std::endl;  
        std::cout << "Version 0.0.1" << std::endl << std::endl;
    }

    template<typename T>
    std::vector<T> uniformNumbers(int len, int low, int high)
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
    std::vector<int> uniformNumbers(int len, int low, int high)
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
    void printVector(std::vector<T> numbers)
    {
        std::cout << "[";
        for(auto & num : numbers)
            std::cout << num << ",";
        std::cout << '\b' << "]" << '\n';
    }

}

#endif