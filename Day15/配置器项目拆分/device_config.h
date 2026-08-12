#pragma once
#include <string>
#include <string_view>
#include <array>
#include <cstdint>
#include <iostream>

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

bool parseRate(std::string_view text, int &rate);
std::string DeviceStateToStr(DeviceState state);
bool StrToDeviceState(std::string_view str, DeviceState &state);
std::string getLine();
CommandResult CommandComplier(std::string_view str, DeviceConfig &device);