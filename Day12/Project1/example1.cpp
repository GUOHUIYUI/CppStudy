#include"example1.h"


std::string_view toString(DeviceStatus state)
{
	switch (state)
	{
	case DeviceStatus::idle:
	{
		return "idle";
	}
	case DeviceStatus::running:
	{
		return "running";
	}
	case DeviceStatus::fault:
	{
		return "fault";
	}
	default:
	{
		return "unknow";
	}
	}

}

std::string_view toString(DeviceStatus1 state)
{
	switch (state)
	{
	case DeviceStatus1::idle:
	{
		return "idle";
	}
	case DeviceStatus1::running:
	{
		return "running";
	}
	case DeviceStatus1::fault:
	{
		return "fault";
	}
	default:
	{
		return "unknow";
	}
	}

}