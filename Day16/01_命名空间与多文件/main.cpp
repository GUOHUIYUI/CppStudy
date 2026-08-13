#include "temperature.h"

#include <iostream>


namespace temp = units::temperature;
int main()
{
	std::cout << units::temperature::celsiusToFahrenheit(0) << '\n';

	std::cout << units::temperature::celsiusToFahrenheit(100) << '\n';

	std::cout << units::temperature::fahrenheitToCelsius(32) << '\n';

	std::cout << temp::celsiusToFahrenheit(0) << '\n';

	std::cout << temp::celsiusToFahrenheit(100) << '\n';

	std::cout << temp::fahrenheitToCelsius(32) << '\n';

	return 0;
}
