#include "device_config.h"
#include<iostream>
int main()
{
	device::config::DeviceConfig device{};
	std::cout << "Enter command: ";
	std::string line{};
	device::config::CommandResult commandState{};
	while (std::getline(std::cin, line))
	{
		if (line == "QUIT") break;
		commandState = device::config::CommandComplier(line, device);
	}
	return 0;
}
