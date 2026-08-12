#include"device_config.h"


int main()
{
	DeviceConfig device{};
	std::cout << "Enter command: ";
	std::string line{};
	CommandResult commandState{};
	while (std::getline(std::cin, line))
	{
		if (line == "QUIT") break;
		commandState = CommandComplier(line, device);
	}
	return 0;
}
