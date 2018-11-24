#include "Intersort.h"

// The type of numbers to be generated
using T = int;

int main()
{
    Intersort::printWelcomeScreen();
    
    std::vector<T> inter_numbers = Intersort::uniformNumbers<T>(200, -5000000, 5000000);
    std::vector<T> quick_numbers = inter_numbers;

    std::chrono::high_resolution_clock::time_point tStart = std::chrono::high_resolution_clock::now();
    std::sort(quick_numbers.begin(), quick_numbers.end());
    std::chrono::high_resolution_clock::time_point tEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> quickspan = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

    tStart = std::chrono::high_resolution_clock::now();
    Intersort::sort(inter_numbers);
    tEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> interspan = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

    std::cout << "\n";
    std::cout << "Intersort = " << std::is_sorted(inter_numbers.begin(), inter_numbers.end()) << "\n";
    std::cout << "Quicksort = " << std::is_sorted(quick_numbers.begin(), quick_numbers.end()) << "\n";


    std::cout << "\n";
    std::cout << "Intersort = \t" << interspan.count() << "\n";
    std::cout << "Quicksort = \t" << quickspan.count() << "\n";

    return 0;
}