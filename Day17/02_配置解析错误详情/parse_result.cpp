#include "parse_result.h"

// 把只供本文件使用的验证函数放入匿名命名空间。
namespace {
	device::config::CommandResultInfo isValidName(std::string_view name) {
		if (name.empty())
		{
			// 有命令但没有参数：缺少参数，而不是非法参数
			return { device::config::CommandResult::missingArgument, "NAME", "NAME requires one value" };
		}
		if (name.size() > 16)
		{
			return { device::config::CommandResult::invalidArgument, "NAME", "NAME must be at most 16 characters" };
		}
		return { device::config::CommandResult::ok, "NAME", "" };
	}
	device::config::CommandResultInfo isValidRate(int rate) {
		// 与 parseRate 保持一致：范围为 1 ~ 1000
		if (rate <= 0 || rate > 1000)
		{
			return { device::config::CommandResult::invalidArgument, "RATE", "RATE must be an integer from 1 to 1000" };
		}
		return { device::config::CommandResult::ok, "RATE", "" };
	}
}
// 在 device::config 命名空间中实现公开成员函数。
namespace device::config {
	CommandResultInfo DeviceConfig::setName(std::string_view name)
	{
		CommandResultInfo result = isValidName(name);
		if (result.succeeded())
		{
			name_ = name;
		}
		return result;
	}
	CommandResultInfo DeviceConfig::setRate(int rate)
	{
		CommandResultInfo result = isValidRate(rate);
		if (result.succeeded())
		{
			rate_ = rate;
		}
		return result;
	}
	void DeviceConfig::setState(DeviceState state)
	{
		state_ = state;
	}

	const std::string &DeviceConfig::name() const
	{
		return name_;
	}
	int DeviceConfig::rate() const
	{
		return rate_;
	}
	DeviceState DeviceConfig::state() const
	{
		return state_;
	}
	CommandResultInfo CommandComplier(std::string_view str, device::config::DeviceConfig &device)
	{
		std::string command{};
		std::string value{};
		size_t index = str.find(' ');
		if (index == std::string::npos)
		{
			command = str;
		}
		else
		{
			command = str.substr(0, index);
			value = str.substr(index + 1);
		}
		if (command == "SHOW")
		{
			std::cout << "Name: " << device.name() << "\n";
			std::cout << "Rate: " << device.rate() << "\n";
			std::cout << "State: " << DeviceStateToStr(device.state()) << "\n";
			return { CommandResult::ok, "SHOW", "" };
		}
		if (command == "NAME")
		{
			return device.setName(value);
		}
		if (command == "RATE")
		{
			if (value.empty())
			{
				// 缺少参数：RATE 后必须跟一个值
				return { CommandResult::missingArgument, "RATE", "RATE requires one value" };
			}
			int rate{};
			if (!parseRate(value, rate))
			{
				// 非数字或超出 1~1000：非法参数
				return { CommandResult::invalidArgument, "RATE", "RATE must be an integer from 1 to 1000" };
			}
			return device.setRate(rate);
		}
		if (command == "STATE")
		{
			if (value.empty())
			{
				return { CommandResult::missingArgument, "STATE", "STATE requires one value" };
			}
			DeviceState state{};
			if (!StrToDeviceState(value, state))
			{
				return { CommandResult::invalidArgument, "STATE", "STATE must be IDLE, OFFLINE or RUNNING" };
			}
			device.setState(state);
			return { CommandResult::ok, "STATE", "" };
		}
		if (command.empty())
		{
			return { CommandResult::emptyInput, "", "" };
		}
		return { CommandResult::unknownCommand, command, "unknown command: " + command };
	}
	std::string CommandResultToStr(CommandResult status)
	{
		switch (status)
		{
		case CommandResult::ok: return "OK";
		case CommandResult::emptyInput: return "EMPTY_INPUT";
		case CommandResult::unknownCommand: return "UNKNOWN_COMMAND";
		case CommandResult::missingArgument: return "MISSING_ARGUMENT";
		case CommandResult::invalidArgument: return "INVALID_ARGUMENT";
		default: return "UNKNOWN";
		}
	}
}



bool parseRate(std::string_view text, int &rate)
{
	if (text == "") return false;

	// 校验是否全为数字
	for (char c : text)
	{
		if (c < '0' || c > '9')
			return false;
	}

	int value = 0;
	for (size_t i = 0; i < text.size(); i++)  // 从左往右
	{
		value = value * 10 + (text[i] - '0');
		if (value > 1000) return false;
	}

	if (value > 0 && value <= 1000)
	{
		rate = value;
		return true;
	}
	return false;
}


std::string DeviceStateToStr(device::config::DeviceState state)
{
	switch (state)
	{
	case device::config::DeviceState::idle: return "IDLE";
	case device::config::DeviceState::offline:return "OFFLINE";
	case device::config::DeviceState::running: return "RUNNING";
	default: return "UNKNOW";
	}
}
bool StrToDeviceState(std::string_view str, device::config::DeviceState &state)
{
	if (str == "IDLE")
	{
		state = device::config::DeviceState::idle;
		return true;
	}
	if (str == "OFFLINE")
	{
		state = device::config::DeviceState::offline;
		return true;
	}
	if (str == "RUNNING")
	{
		state = device::config::DeviceState::running;
		return true;
	}
	return false;
}

std::string getLine()
{
	std::string line;
	std::getline(std::cin, line);
	return line;
}

