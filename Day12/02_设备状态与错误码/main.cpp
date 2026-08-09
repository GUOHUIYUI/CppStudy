#include <cstdint>
#include <iostream>
#include <string_view>

enum class CommandError :std::uint8_t
{
	emptyInput = 0,
	invalidCommand = 1,
	invalidData = 2,
	success = 3
};

CommandError CommandCheck(std::string_view command)
{
	if (command.empty())
	{
		return CommandError::emptyInput;
	}
	if (command == "START" || command == "STOP" || command == "SET RATE")
	{
		return CommandError::success;
	}
	return CommandError::invalidCommand;

}
std::string_view toStrig(CommandError state)
{
	switch (state)
	{
	case CommandError::success: return "success";
	case CommandError::emptyInput: return "emptyInput";
	case CommandError::invalidCommand: return "invalidCommand";
	case CommandError::invalidData: return "invalidData";
	default:return "unknow";
	}
}

int main()
{
	//验证
	std::cout << toStrig(CommandCheck("START")) << "\n";
	std::cout << toStrig(CommandCheck("STOP")) << "\n";
	std::cout << toStrig(CommandCheck("SET RATE")) << "\n";
	std::cout << toStrig(CommandCheck("NULL")) << "\n";
	std::cout << toStrig(CommandCheck("")) << "\n";



	return 0;
}
