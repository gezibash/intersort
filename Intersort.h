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
    std::vector<T> interpolate(std::vector<T> x, std::vector<T> y, std::vector<T> xq)
    {
        std::vector<T> yq;
        for(auto &num : xq)
            yq.push_back(y[0] + ((y[1] - y[0]) / (x[1] - x[0])) * (num - x[0]));
        return yq;
    }

    template<typename T>
    void sort(std::vector<T> &numbers)
    {
        
    }
}

#endif