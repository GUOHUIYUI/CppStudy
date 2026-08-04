#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


constexpr bool isCelsiusValid(double celsius)
{
    return celsius < -273.14 ? false : true;
}
constexpr double celsiusToFahrenheit(double celsius)
{
    return celsius * 9 / 5 + 32;
}
bool convertTemperature(double celsius, double& fahrenheit);
bool convertTemperature(int celsius, double& fahrenheit);

static_assert(isCelsiusValid(-300) == false, "celsius err");
static_assert(celsiusToFahrenheit(5) == 41.0, "celsius err");
static_assert(isCelsiusValid(0) == true, "celsius err");
static_assert(isCelsiusValid(-273.14) == true, "celsius err");

void check(double celsius, double& actual)
{
    double tmp{ actual };
    if (convertTemperature(celsius, actual))
    {
        std::cout << "celsius =" << celsius << "     fahrenheit =" << actual << "\n";
    }
    else
    {
        std::cout << "ERROR" << "expect=   "<< tmp<<"   actual=" << actual << std::endl;
    }
}
int main()
{
    double actual{};
   
    check(-300, actual);
    check(0, actual);
    check(-273.14, actual);
    check(100, actual);
    check(200, actual);
    return 0;
}

bool convertTemperature(double celsius, double& fahrenheit)
{
    if (isCelsiusValid(celsius))
    {
        double num = celsiusToFahrenheit(celsius);
        fahrenheit = num;
        return true;
    }
    return false;
}
bool convertTemperature(int celsius, double& fahrenheit)
{
    double num = static_cast<double>(celsius);
    return convertTemperature(num, fahrenheit);
}

