#include"temperature.h"
#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    std::cout << celsiusToFahrenheit(25.0) << "\n";
    //只有声明没有定义，会报链接错误
    std::cout << fahrenheitToCelsius(77.0) << "\n";

    return 0;
}