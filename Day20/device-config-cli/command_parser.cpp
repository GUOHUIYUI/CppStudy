#include "command_parser.h"

#include <cctype>
#include <stdexcept>
#include <string>

namespace device {

namespace {

bool IsAllDigits(std::string_view text)
{
	if (text.empty())
	{
		return false;
	}
	for (char c : text)
	{
		if (!std::isdigit(static_cast<unsigned char>(c)))
		{
			return false;
		}
	}
	return true;
}

std::string_view Trim(std::string_view text)
{
	size_t first = text.find_first_not_of(" \t");
	if (first == std::string_view::npos)
	{
		return {};
	}
	size_t last = text.find_last_not_of(" \t");
	return text.substr(first, last - first + 1);
}

const char* StateToString(DeviceState state)
{
	switch (state)
	{
	case DeviceState::kOff:     return "kOff";
	case DeviceState::kOn:      return "kOn";
	case DeviceState::kUnknown: return "kUnknown";
	}
	return "kUnknown";
}

} // namespace

// 在这里实现命令解析。
CommandInfo CommandComplier(std::string_view cmd, DeviceConfig& device, std::string& output)
{
	// 1. 空输入
	if (cmd.empty())
	{
		return { CommandResult::emptyInput, "command", "empty input" };
	}

	// 2. 拆分命令与参数：命令与参数之间至少一个空格
	size_t space = cmd.find(' ');
	std::string_view command = cmd.substr(0, space);
	std::string_view value = (space == std::string_view::npos)
		? std::string_view{}
		: Trim(cmd.substr(space + 1));

	// 3. SHOW：显示当前配置
	if (command == "SHOW")
	{
		output = "name: " + device.GetName() + "\n";
		output += "rate: " + std::to_string(device.GetRate()) + "\n";
		output += std::string("state: ") + StateToString(device.GetState()) + "\n";
		return { CommandResult::ok, "show", "ok" };
	}

	// 4. NAME <text>
	if (command == "NAME")
	{
		if (value.empty())
		{
			return { CommandResult::missingArgument, "name", "name argument missing" };
		}
		return device.SetName(value);
	}

	// 5. RATE <integer>
	if (command == "RATE")
	{
		if (value.empty())
		{
			return { CommandResult::missingArgument, "rate", "rate argument missing" };
		}
		if (!IsAllDigits(value))
		{
			return { CommandResult::invalidArgument, "rate", "rate must be an integer" };
		}
		int rate = 0;
		try
		{
			rate = std::stoi(std::string(value));
		}
		catch (const std::out_of_range&)
		{
			return { CommandResult::invalidArgument, "rate", "rate out of range" };
		}
		return device.SetRate(rate);
	}

	// 6. STATE <value>
	if (command == "STATE")
	{
		if (value.empty())
		{
			return { CommandResult::missingArgument, "state", "state argument missing" };
		}
		DeviceState state = DeviceState::kUnknown;
		if (value == "kOff")
		{
			state = DeviceState::kOff;
		}
		else if (value == "kOn")
		{
			state = DeviceState::kOn;
		}
		else if (value == "kUnknown")
		{
			state = DeviceState::kUnknown;
		}
		else
		{
			return { CommandResult::invalidArgument, "state", "state must be kOff/kOn/kUnknown" };
		}
		return device.SetState(state);
	}

	// 7. 未知命令
	return { CommandResult::unknownCommand, "command", "unknown command" };
}

} // namespace device
