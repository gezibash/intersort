#ifndef INTERSORT_H
#define INTERSORT_H

#include "Helpers.h"

namespace Intersort
{
    template<typename T>
    void presort(std::vector<T> &numbers)
    {
        auto [minIndex, maxIndex] = std::minmax_element(numbers.begin(), numbers.end());
        std::iter_swap(numbers.begin(), minIndex);
        std::iter_swap(numbers.end()-1, maxIndex);
    }

    template<typename T>
    int interpolate(T &xq, std::vector<T> &x, std::vector<int> &y)
    {
        int i = 1;
        while(xq > x[i])
            i++;        

        double slope = double(y[i] - y[i-1]) / double(x[i] - x[i-1]);
        return std::round(slope * (xq - x[i-1]) + y[i-1]);
    }

    template<typename T>
    std::vector<int> interpolate(std::vector<T> &xq, std::vector<T> &x, std::vector<int> &y)
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
        // We will initially presort the array
        presort(numbers);

        // On some special cases the min and max swap
        // we want to make sure they are swapped back in place
        if(*numbers.begin() > *(numbers.end()-1))
            std::iter_swap(numbers.begin(), numbers.end() - 1);
        
        // Create interpolants
        std::vector<T>   x  = {*numbers.begin(), *(numbers.end()-1)};
        std::vector<int> y  = {0, (int)numbers.size()};

        // Create main container
        std::vector<std::vector<T>> container;
        container.reserve(numbers.size());

        printVector(numbers);

        // Main loop
        int location;
        for(auto & num : numbers)
        {
            location = interpolate(num, x, y);
            std::cout << num << " => " << location << std::endl;

            if(container[location].size() == 0) {
                container[location].push_back(num);
            } else {

                std::cout << num << " <=> " << location << std::endl;
                auto & tower = container[location];

                printVector(tower);

                int i = 0;

                while(num > tower[i]) i++;
                
                std::cout << "will insert " << num << " at " << i << "\n";

                tower.insert((tower.begin() + i), num);

                printVector(tower);
            }
        }
    }
}

#endif