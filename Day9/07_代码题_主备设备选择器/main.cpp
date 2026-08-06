#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct DeviceHandle {
	int id;
	bool online;
};

const DeviceHandle *selectDevice(bool primaryOnline, bool backupOnline, const DeviceHandle &primary, const DeviceHandle &backup)
{
	if (primaryOnline)
	{
		return &primary;
	}
	else if (backupOnline)
	{
		return &backup;
	}

	return nullptr;
}

int main()
{

	DeviceHandle primary{ 1,true };
	DeviceHandle backup{ 2,true };
	const DeviceHandle *receive{ nullptr };
	receive = selectDevice(true, true, primary, backup);
	if (receive != nullptr)
	{
		std::cout << receive->id << std::endl;
	}
	receive = selectDevice(false, true, primary, backup);
	if (receive != nullptr)
	{
		std::cout << receive->id << std::endl;
	}
	receive = selectDevice(true, false, primary, backup);
	if (receive != nullptr)
	{
		std::cout << receive->id << std::endl;
	}
	receive = selectDevice(false, false, primary, backup);
	if (receive != nullptr)
	{
		std::cout << receive->id << std::endl;
	}
	return 0;
}
