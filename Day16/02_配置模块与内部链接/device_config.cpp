#include "device_config.h"

// 把只供本文件使用的验证函数放入匿名命名空间。
namespace {
	bool isValidName(std::string_view name) {
		if (name == "" || name.size() > 16)return false;
		return true;
	}
	bool isValidRate(int rate) {
		if (rate <= 0 || rate > 1000)return false;
		return true;
	}
}
// 在 device::config 命名空间中实现公开成员函数。
namespace device::config {
	bool DeviceConfig::setName(std::string_view name)
	{
		if (isValidName(name))
		{
			name_ = name;
			return true;
		}
		return false;
	}
	bool DeviceConfig::setRate(int rate)
	{
		if (isValidRate(rate))
		{
			rate_ = rate;
			return true;
		}
		return false;
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
	CommandResult CommandComplier(std::string_view str, device::config::DeviceConfig &device)
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
			return CommandResult::ok;
		}
		else if (command == "NAME")
		{
			if (!device.setName(value))
			{
				return  CommandResult::invalidArgument;
			}
			return CommandResult::ok;
		}
		else if (command == "RATE")
		{
			int rate{};
			if (parseRate(value, rate))
			{
				device.setRate(rate);
				return CommandResult::ok;
			}
			else {
				return  CommandResult::invalidArgument;
			}
		}
		else if (command == "STATE")
		{
			DeviceState state{};
			if (StrToDeviceState(value, state))
			{
				device.setState(state);
				return CommandResult::ok;
			}
			return  CommandResult::invalidArgument;

		}
		else if (command == "SAMPLES")
		{
			const std::array<int, 8> samples{ 120, 118, 121, 125, 119, 123, 122, 120 };
			int max{ samples[0] }, min{ samples[0] }, sum{};
			double avg{};
			for (int sample : samples)
			{
				sum += sample;
				if (sample > max)max = sample;
				if (sample < min)min = sample;
			}
			avg = static_cast<double>(sum) / samples.size();
			std::cout << "max: " << max << "\n";
			std::cout << "min: " << min << "\n";
			std::cout << "avg: " << avg << "\n";
			return  CommandResult::ok;
		}
		else if (command == "")
		{
			return  CommandResult::emptyInput;
		}
		else {
			return  CommandResult::unknownCommand;
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

