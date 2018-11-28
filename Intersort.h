#ifndef INTERSORT_H
#define INTERSORT_H

#include "Helpers.h"
#include "Distributions.h"

// Formula to estimate collisions - f(n) = floor(n/e)

namespace Intersort
{
    template<typename T>
    constexpr void presort(std::vector<T> &numbers)
    {
        auto [minIndex, maxIndex] = std::minmax_element(numbers.begin(), numbers.end());
        std::iter_swap(numbers.begin(), minIndex);
        std::iter_swap(numbers.end()-1, maxIndex);

        // On some special cases the min and max swap
        // we want to make sure they are swapped back in place
        if(*numbers.begin() > *(numbers.end()-1))
            std::iter_swap(numbers.begin(), numbers.end() - 1);
    }

    std::vector<int> partition(int len)
    {
        std::vector<int> indices;
        int length = len;

        indices.push_back(0);
        len = floor(len / 2);
        while(len != 1)
        {
            indices.push_back(len);
            len = floor(len / 2);
        }

        unsigned int count = indices.size();
        for(int i = 2; i < count; i++)
        {   
            indices.push_back(floor(length/2) + indices[i]);
        }
        
        count = indices.size();
        for(int i = 2; i < count; i++)
        {   
            indices.push_back(length - indices[i]);
        }

        std::sort(indices.begin(), indices.end());

        indices.erase(std::unique(indices.begin(), indices.end()), indices.end());

        indices.push_back(length - 1);

        return indices;
    }

    template<typename T>
    std::vector<T> nth_element(std::vector<T> &numbers, std::vector<int> &indices)
    {
        std::vector<T> nums;
        nums.reserve(indices.size());

        for(auto & index : indices)
        {
            std::nth_element(numbers.begin(), numbers.begin() + index, numbers.end());
            nums.push_back(*(numbers.begin() + index));
        }
        
        return nums;
    }

    template<typename T>
    constexpr int interpolate(T &xq, std::vector<T> &x, std::vector<int> &y)
    {
        int i = 1;
        while(xq > x[i])
            i++;        

        double slope = double(y[i] - y[i-1]) / double(x[i] - x[i-1]);
        return round(slope * (xq - x[i-1]) + y[i-1]);
    }

    template<typename T>
    constexpr std::vector<int> interpolate(std::vector<T> &xq, std::vector<T> &x, std::vector<int> &y)
    {
        std::vector<int> yq;
        yq.reserve(xq.size());

        for(auto & num : xq)
            yq.push_back(interpolate(num, x, y));
        
        return yq;
    }

    template<typename T>
    void sort(std::vector<T> &numbers, unsigned int &collisions, bool usePiecewise = false, bool reportTime = false, bool serialize = false)
    {
        std::vector<T>   x;
        std::vector<int> y;

        auto tStart = std::chrono::high_resolution_clock::now();
        if(!usePiecewise)
        {
            presort(numbers);
            x  = {*numbers.begin(), *(numbers.end()-1)};
            y  = {0, (int)numbers.size() - 1};
        }
        else
        {
            y = partition(numbers.size());
            x = nth_element(numbers, y);
        }
        auto tEnd = std::chrono::high_resolution_clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

        if(reportTime)
            std::cout << "[presort] " << delta.count() << std::endl;

        // Create main container
        tStart = std::chrono::high_resolution_clock::now();
        std::vector<std::multiset<T, std::less_equal<T>>> container;
        std::multiset<T, std::less_equal<T>> empty;
        for(int i = 0; i < numbers.size(); i++)
            container.push_back(empty);

        // Main loop
        unsigned int location;
        for(auto & num : numbers)
        {
            location = interpolate(num, x, y);            
            container[location].insert(num);
        }
        tEnd = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

        if(reportTime)
            std::cout << "[main loop] " << delta.count() << std::endl;

        tStart = std::chrono::high_resolution_clock::now();
        // Refill loop
        int i = -1;
        for(auto & set : container)
            for(auto & num : set)
                numbers[++i] = num;
        tEnd = std::chrono::high_resolution_clock::now();
        delta = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

        if(reportTime)
            std::cout << "[refill] " << delta.count() << std::endl;

        if(serialize)
        {
            tStart = std::chrono::high_resolution_clock::now();
            serializeContainer(container, collisions);
            tEnd = std::chrono::high_resolution_clock::now();
            delta = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

            if(reportTime)
                std::cout << "[serialize] " << delta.count() << std::endl;
        }
    }
}

#endif