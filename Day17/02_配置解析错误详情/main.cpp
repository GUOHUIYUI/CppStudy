#include "parse_result.h"

#include <iostream>

int main()
{
	device::config::DeviceConfig device{};
	std::cout << "Enter command: ";
	std::string line{};
	while (std::getline(std::cin, line))
	{
		if (line == "QUIT") break;
		const auto result = device::config::CommandComplier(line, device);
		if (!result.succeeded())
		{
			// 统一的错误显示出口
			std::cout << "[" << device::config::CommandResultToStr(result.status) << "] ";
			if (!result.field.empty())
			{
				std::cout << result.field << ": ";
			}
			std::cout << result.reason << '\n';
		}
	}
    return 0;
}
