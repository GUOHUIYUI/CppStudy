#include "device_config.h"

#include <iostream>
#include <stdexcept>

int main()
{


	try {
		DeviceConfig device{ "",1,DeviceState::kError };
		std::cout<<device.name()<<'\n';
		std::cout << device.rate() << '\n'; 
	}
	catch (std::invalid_argument& error) {
		std::cout << error.what() << '\n';
	}
	try {
        DeviceConfig device{ "sensor-a",1,DeviceState::kError };
        std::cout << device.name() << '\n';
        std::cout << device.rate() << '\n';
    }
    catch (std::invalid_argument& error) {
        std::cout << error.what() << '\n';
    }
    try {
        DeviceConfig device{ "sensor-a",1000,DeviceState::kError };
        std::cout << device.name() << '\n';
        std::cout << device.rate() << '\n';
    }
    catch (std::invalid_argument& error) {
        std::cout << error.what() << '\n';
    }
    try {
        DeviceConfig device{ "sensor-a1111111111",1000,DeviceState::kError };
        std::cout << device.name() << '\n';
        std::cout << device.rate() << '\n';
    }
    catch (std::invalid_argument& error) {
        std::cout << error.what() << '\n';
    }
    try {
        DeviceConfig device{ "sensor-a",1001,DeviceState::kError };
        std::cout << device.name() << '\n';
        std::cout << device.rate() << '\n';
    }
    catch (std::invalid_argument& error) {
        std::cout << error.what() << '\n';
    }

    return 0;
}
