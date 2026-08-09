#include <cstdint>
#include <iostream>
#include <string_view>

enum class DeviceState {
	offline,
	idle,
	running,
	fault
};
std::string_view toString(DeviceState state);
bool canStart(DeviceState state);


int main()
{
	
	for (auto state : { DeviceState::offline,DeviceState::idle,DeviceState::running,DeviceState::fault }) {
        std::cout << "state:" << toString(state) << " canStart:" << (canStart(state) ? "true" : "false") << "\n";
    }
	return 0;
}
std::string_view toString(DeviceState state)
{
	switch (state)
	{
	case DeviceState::fault: return "fault";
	case DeviceState::idle: return "idle";
	case DeviceState::running: return "running";
	case DeviceState::offline: return "offline";
	default:return "unknow";

	}
}
bool canStart(DeviceState state)
{
	return state == DeviceState::idle;
}
