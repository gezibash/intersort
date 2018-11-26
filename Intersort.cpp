#include "Intersort.h"

// The type of numbers to be generated
using T = double;

template<typename T>
void benchmark(int len, T a, T b, bool piecewise, bool report, bool serialize = true)
{
    std::vector<T> inter_numbers = Intersort::exponentialDistribution<T>(len, a);
    unsigned int collisions = 0;

    auto tStart = std::chrono::high_resolution_clock::now();
    Intersort::sort(inter_numbers, collisions, piecewise, report, serialize);
    auto tEnd = std::chrono::high_resolution_clock::now();
    auto interspan = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

    Intersort::serializeVector(inter_numbers);

    std::cout << collisions << "," << interspan.count() << "," << std::is_sorted(inter_numbers.begin(), inter_numbers.end()) << "\n"; 
}

int main(int argc, char* argv[])
{
    benchmark<T>(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), false, true);
    std::cout << std::endl;
    benchmark<T>(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), true, true);
    return 0;
}