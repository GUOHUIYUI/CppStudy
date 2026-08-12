#include "temperature.h"

#include <iostream>

int main()
{
    std::cout << celsiusToFahrenheit(0) << "\n";
    std::cout << celsiusToFahrenheit(100) << "\n";
    std::cout << fahrenheitToCelsius(33) << "\n";
    return 0;
}
