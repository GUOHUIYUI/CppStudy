#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
//const 靠近谁修饰谁
//const DeviceHandle* handle :可以通过修改handle指向别处，但是不能修改设备状态，适合与只读接口
//DeviceHandle* const handle :可以通过修改设备状态，但是不能修改handle指向，适合与可读写接口  但是可以为空
//DeviceHandle* handle  :可以修改设备状态，需要先判空
//const DeviceHandle& handle :设备必须存在，并且函数只读

struct DeviceHandle {
	int id;
	bool status;
};

void makeOffline(DeviceHandle &handle)
{
	handle.status = false;
}

int main()
{
	DeviceHandle handle{ 1,true };
	makeOffline(handle);
	std::cout << handle.status << std::endl;

	return 0;
}
