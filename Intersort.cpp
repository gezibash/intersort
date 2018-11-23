#include "Intersort.h"

int main()
{
    Intersort::printWelcomeScreen();
    
    std::vector<int> numbers = Intersort::uniformNumbers<int>(20, 0, 100);

    Intersort::printVector(numbers);
    Intersort::presort(numbers);
    Intersort::printVector(numbers);

    return 0;
}