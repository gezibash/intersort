#include "Intersort.h"

// The type of numbers to be generated
using T = int;

int main()
{
    Intersort::printWelcomeScreen();
    
    std::vector<T> numbers = Intersort::uniformNumbers<T>(20, 0, 100);

    Intersort::sort(numbers);

    return 0;
}