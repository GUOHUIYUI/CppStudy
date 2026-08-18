#include "device_config.h"

#include <stdexcept>

using namespace device;

// 在这里实现DeviceConfig。
device::DeviceConfig::DeviceConfig(int rate, std::string_view name, DeviceState state)
	: rate_(rate), name_(name), state_(state)
{
	if (rate < 1 || rate > 1000)
	{
		throw std::invalid_argument("invalid rate");
	}
	if (name.empty() || name.size() > 16)
	{
		throw std::invalid_argument("invalid name");
	}
}

CommandInfo device::DeviceConfig::SetRate(int rate)
{
	if (rate < 1 || rate > 1000)
	{
		return { CommandResult::invalidArgument, "rate", "rate invalid" };
	}
	rate_ = rate;
	return { CommandResult::ok, "succeed", "ok" };
}

CommandInfo device::DeviceConfig::SetName(std::string_view name)
{
	if (name.empty() || name.size() > 16)
	{
		return { CommandResult::invalidArgument, "name", "name invalid" };
	}
	name_ = std::string(name);
	return { CommandResult::ok, "succeed", "ok" };
}

CommandInfo device::DeviceConfig::SetState(DeviceState state)
{
	state_ = state;
	return { CommandResult::ok, "succeed", "ok" };
}

int device::DeviceConfig::GetRate() const
{
	return rate_;
}

const std::string& device::DeviceConfig::GetName() const
{
	return name_;
}

DeviceState device::DeviceConfig::GetState() const
{
	return state_;
}
