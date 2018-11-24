#ifndef INTERSORT_H
#define INTERSORT_H

#include "Helpers.h"

namespace Intersort
{    
    template<typename T>
    constexpr void presort(std::vector<T> &numbers)
    {
        auto [minIndex, maxIndex] = std::minmax_element(numbers.begin(), numbers.end());
        std::iter_swap(numbers.begin(), minIndex);
        std::iter_swap(numbers.end()-1, maxIndex);
    }

    template<typename T>
    constexpr int interpolate(T &xq, std::vector<T> &x, std::vector<int> &y)
    {
        int i = 1;
        while(xq > x[i])
            i++;        

        double slope = double(y[i] - y[i-1]) / double(x[i] - x[i-1]);
        return floor(slope * (xq - x[i-1]) + y[i-1]);
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
    void sort(std::vector<T> &numbers)
    {
        presort(numbers);

        // On some special cases the min and max swap
        // we want to make sure they are swapped back in place
        if(*numbers.begin() > *(numbers.end()-1))
            std::iter_swap(numbers.begin(), numbers.end() - 1);
        
        // Create interpolants
        std::vector<T>   x  = {*numbers.begin(), *(numbers.end()-1)};
        std::vector<int> y  = {0, (int)numbers.size()};

        // Create main container
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
        
        int i = -1;
        for(auto & set : container)
            for(auto & num : set)
                numbers[++i] = num;

        printContainer(container);
    }
}

#endif