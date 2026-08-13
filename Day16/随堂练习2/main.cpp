#include"temperature.h"
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    std::cout << units::temperature::fahrenheitToCelsius(1) << '\n';

    return 0;
}