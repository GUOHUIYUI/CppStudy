#ifndef DAY18_DEVICE_CONFIG_H
#define DAY18_DEVICE_CONFIG_H

#include <string>
#include<stdexcept>
// 在这里声明设备状态和DeviceConfig。
enum class DeviceState {
	kOff,
	kOn,
	kError
};

class DeviceConfig
{
public:
	DeviceConfig(std::string name, int rate, DeviceState status);


	const std::string& name() const;
	int rate()const;
	DeviceState status()const;



private:
	std::string name_;
	int rate_;
	DeviceState status_;
};


#endif
