#ifndef DAY16_DEVICE_CONFIG_H
#define DAY16_DEVICE_CONFIG_H

#include <string>
#include <string_view>
#include <iostream>
#include <array>
// 在 device::config 命名空间中声明 DeviceConfig。



namespace device::config {
	enum class DeviceState {
		offline,
		idle,
		running
	};

	enum class CommandResult {
		ok,
		emptyInput,
		unknownCommand,
		missingArgument,
		invalidArgument
	};
	class DeviceConfig {
	public:
		bool setName(std::string_view name);
		bool setRate(int rate);
		void setState(DeviceState state);
		const std::string &name() const;
		int rate() const;
		DeviceState state() const;

	private:
		std::string name_{ "device" };
		int rate_{ 100 };
		DeviceState state_{ DeviceState::offline };
	};
	CommandResult CommandComplier(std::string_view str,DeviceConfig &device);
}


bool parseRate(std::string_view text, int &rate);
std::string DeviceStateToStr(device::config::DeviceState state);
bool StrToDeviceState(std::string_view str, device::config::DeviceState &state);
std::string getLine();


#endif
