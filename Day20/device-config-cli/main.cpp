#include "command_parser.h"

#include <iostream>
#include <string>

int main()
{
	device::DeviceConfig device(100, "device", device::DeviceState::kOff);

	std::string line;
	while (true)
	{
		std::cout << "> " << std::flush;
		if (!std::getline(std::cin, line))
		{
			break; // EOF
		}
		// QUIT 结束程序
		if (line == "QUIT")
		{
			break;
		}

		std::string output;
		device::CommandInfo info = device::CommandComplier(line, device, output);

		if (info.succeed())
		{
			if (!output.empty())
			{
				std::cout << output;
			}
		}
		else
		{
			std::cout << "error: " << info.reason << " (" << info.field << ")\n";
		}
	}

	return 0;
}
