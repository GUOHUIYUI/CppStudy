#include "device_config.h"

// 在这里实现DeviceConfig。
DeviceConfig::DeviceConfig(std::string name, int rate, DeviceState status) 
:
	name_{ std::move(name) },
rate_{ rate },
status_{ status }
{
	if (name_.empty() || name_.size() > 16)
	{
		throw std::invalid_argument{ "name must.size() be1-16 " };
	}
	if (rate_ < 0 || rate_>1000)
	{
		throw std::invalid_argument{ "rate must be 0-1000 " };
	}
}

const std::string&  DeviceConfig::  name() const {
	return name_;
}

int DeviceConfig::rate()const {
	return rate_;
}

DeviceState DeviceConfig::status()const
{
	return status_;
}