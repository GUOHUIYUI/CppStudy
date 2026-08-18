#ifndef DAY20_DEVICE_CONFIG_H
#define DAY20_DEVICE_CONFIG_H

#include <string>
#include <string_view>

// 在这里声明DeviceConfig及相关强类型状态。


namespace device {
	enum class DeviceState {
		kOff,
        kOn,
        kUnknown
	};
	enum class CommandResult {
		ok,
        missingArgument,
        invalidArgument,
        unknownCommand,
		emptyInput
	};
	struct CommandInfo {
		CommandResult result{ CommandResult::ok };
		std::string_view field{};
        std::string_view reason{};
		bool succeed() const 
		{
			return result == CommandResult::ok;
		}
	};
	class DeviceConfig {
	public:
		DeviceConfig(int rate, std::string_view name, DeviceState result);

		CommandInfo SetRate(int rate);
        CommandInfo SetName(std::string_view name);
        CommandInfo SetState(DeviceState state);

		int GetRate()const;
		const std::string& GetName()const;
        DeviceState GetState()const;
	private:
		int rate_;
		std::string name_;
		DeviceState state_;
	};
}



#endif
