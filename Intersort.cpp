#include "Intersort.h"

// The type of numbers to be generated
using T = int;
int main(int argc, char* argv[])
{
    std::vector<T> inter_numbers = Intersort::uniformNumbers<T>(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    unsigned int collisions = 0;

    auto tStart = std::chrono::high_resolution_clock::now();
    Intersort::sort(inter_numbers, collisions);
    auto tEnd = std::chrono::high_resolution_clock::now();
    auto interspan = std::chrono::duration_cast<std::chrono::duration<double>> (tEnd - tStart);

    Intersort::serializeVector(inter_numbers);

    std::cout << collisions << "," << interspan.count() << "\n";

    return 0;
}