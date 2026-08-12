#include <array>
#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>

enum class DeviceState {
	offline,
	idle,
	running
};

enum class CommandResult {
	ok,
	emptyInput,
	unknownCommand,
	missingArgument,
	invalidArgument
};

class DeviceConfig {
public:
	bool setName(std::string_view name)
	{
		if (name == "" || name.size() > 16)return false;
		name_ = name;
		return true;
	}
	bool setRate(int rate)
	{
		if (rate <= 0 || rate > 1000)return false;
		rate_ = rate;
		return true;
	}
	void setState(DeviceState state)
	{
		state_ = state;
	}

	const std::string &name() const
	{
		return name_;
	}
	int rate() const
	{
		return rate_;
	}
	DeviceState state() const
	{
		return state_;
	}

private:
	std::string name_{ "device" };
	int rate_{ 100 };
	DeviceState state_{ DeviceState::offline };
};

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


std::string DeviceStateToStr(DeviceState state)
{
	switch (state)
	{
	case DeviceState::idle: return "IDLE";
	case DeviceState::offline:return "OFFLINE";
	case DeviceState::running: return "RUNNING";
	default: return "UNKNOW";
	}
}
bool StrToDeviceState(std::string_view str, DeviceState &state)
{
	if (str == "IDLE")
	{
		state = DeviceState::idle;
		return true;
	}
	if (str == "OFFLINE")
	{
		state = DeviceState::offline;
		return true;
	}
	if (str == "RUNNING")
	{
		state = DeviceState::running;
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

CommandResult CommandComplier(std::string_view str, DeviceConfig &device)
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
int main()
{
	DeviceConfig device{};
	std::cout << "Enter command: ";
	std::string line{};
	CommandResult commandState{};
	while (std::getline(std::cin, line))
	{		if (line == "QUIT") break;
		commandState = CommandComplier(line, device);
	}
	return 0;
}
