#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct DeviceHandle {
	int id;
	bool online;
};
//为什么设备用指针，结果用引用? 因为设备允许不存在  但是返回结果不允许不存在
bool queryDevice(const DeviceHandle *device, int &status)
{
	if (device == nullptr)
	{
		return false;
	}
	if (device->online == false)
	{
		return  false;
	}
	if (device->id > 255 || device->id < 0)
	{
		return false;
	}
	status = device->id * 10;
	return true;
}

int main()
{
	DeviceHandle device{ 0,true };
	int status{ -1 };
	std::cout << queryDevice(nullptr, status) << "   " << status << std::endl;
	std::cout << queryDevice(&device, status) << "   " << status << std::endl;
	device.id = 255;
	std::cout << queryDevice(&device, status) << "   " << status << std::endl;
	device.online = false;
	std::cout << queryDevice(&device, status) << "   " << status << std::endl;
	device.id = -1;
	std::cout << queryDevice(&device, status) << "   " << status << std::endl;
	device.id = 256;
	std::cout << queryDevice(&device, status) << "   " << status << std::endl;
	return 0;
}
