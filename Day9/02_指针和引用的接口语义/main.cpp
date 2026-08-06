#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

struct DeviceHandle {
	int id;
};

//两个接口的区别在于  若允许传入对象不存在，则使用指针 若不允许传入对象不存在，则使用引用
bool resetDevice(DeviceHandle &handle)
{
	handle.id = 0;
	return true;
}

bool readDevice(const DeviceHandle *handle, int &output)
{
	if (handle == nullptr || handle->id < 0 || handle->id > 255)
	{
		return false;
	}
	output = handle->id;
	return true;
}


int main()
{
	DeviceHandle handle{ 256 };
	int device_id{ -1 };
	std::cout << readDevice(&handle, device_id) << "   " << device_id << std::endl;
	device_id = -1;
	std::cout << readDevice(nullptr, device_id) << "   " << device_id << std::endl;

	return 0;
}
