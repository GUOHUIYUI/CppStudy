#ifndef DAY17_PARSE_RESULT_H
#define DAY17_PARSE_RESULT_H

#include <string>
#include <string_view>
#include <iostream>
#include <array>


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
		invalidArgument,
		
	};
	struct CommandResultInfo {
		CommandResult status{ CommandResult::ok };
		std::string field;
		std::string reason;
		bool succeeded() const {
			return status == CommandResult::ok;
		}
	};
	class DeviceConfig {
	public:
		CommandResultInfo setName(std::string_view name);
		CommandResultInfo setRate(int rate);
		void setState(DeviceState state);
		const std::string &name() const;
		int rate() const;
		DeviceState state() const;

	private:
		std::string name_{ "device" };
		int rate_{ 100 };
		DeviceState state_{ DeviceState::offline };
	};
	CommandResultInfo CommandComplier(std::string_view str, DeviceConfig &device);
	std::string CommandResultToStr(CommandResult status);
}


bool parseRate(std::string_view text, int &rate);
std::string DeviceStateToStr(device::config::DeviceState state);
bool StrToDeviceState(std::string_view str, device::config::DeviceState &state);
std::string getLine();


#endif
