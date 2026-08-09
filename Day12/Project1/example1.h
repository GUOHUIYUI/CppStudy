#include<iostream>
#include<string_view>

enum class	DeviceStatus {
	idle,
	running,
	fault	
};

enum class	DeviceStatus1 {
	idle,
	running,
	fault,
	stopping

};

std::string_view toString(DeviceStatus state);
std::string_view toString(DeviceStatus1 state);


