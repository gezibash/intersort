#include "Intersort.h"

// The type of numbers to be generated
using T = double;

template<typename T>
void benchmark(std::vector<T> numbers, bool piecewise, bool report, bool serialize = true)
{
    unsigned int collisions = 0;
    auto tStart = std::chrono::high_resolution_clock::now();
    Intersort::sort(numbers, collisions, piecewise, report, serialize);
    auto tEnd = std::chrono::high_resolution_clock::now();
    auto interspan = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);
    if(serialize) Intersort::serializeVector(numbers);

    std::cout << "coll = " << collisions << "\t";
    std::cout << "ratio = " << double(collisions) / double(numbers.size()) << "\t\t";
    std::cout << "sorted = " << std::is_sorted(numbers.begin(), numbers.end()) << "\t";
    std::cout << "time = " << interspan.count() << "s\n";
}

template<typename T>
void test(int len)
{
    Intersort::printWelcomeScreen();
    std::cout << "\n";

    // Uniform Distribution
    int low = Intersort::randNumber<T>(-len, len);
    int high = low * Intersort::randNumber<T>(1, len/5);

    std::cout << "------------- [Uniform Distribution] -----------\n";
    std::cout << "low = " << low << "\t" << "high = " << high << "\n";
    std::cout << "------------------------------------------------\n";
    
    std::vector<T> numbers = Intersort::uniformDistribution<T>(len, low, high);
    benchmark(numbers, false, false);
    benchmark(numbers, true, false);

    std::cout << "\n";

    T mean = Intersort::randNumber<T>(0, 1);
    T std  = Intersort::randNumber<T>(0, 1);
    std::cout << "------------- [Normal Distribution] -----------\n";
    std::cout << "mu = " << mean << "\t" << "s = " << std << "\n";
    std::cout << "------------------------------------------------\n";
    numbers = Intersort::normalDistribution<T>(len, mean, std);
    benchmark(numbers, false, false);
    benchmark(numbers, true, false);

    std::cout << "\n";

    T lambda = Intersort::randNumber<T>(0,5);
    std::cout << "------------- [Exponential Distribution] -----------\n";
    std::cout << "lambda = " << lambda << "\n";
    std::cout << "------------------------------------------------\n";
    numbers = Intersort::exponentialDistribution<T>(len, lambda);
    benchmark(numbers, false, false);
    benchmark(numbers, true, false);

    std::cout << "\n";
}

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        test<double>(atoi(argv[1]));
    }
    else
    {
        test<double>(1000);      
    }

    //std::vector<int> parts = Intersort::partition(atoi(argv[1]));
    //Intersort::printVector(parts);

    return 0;
}