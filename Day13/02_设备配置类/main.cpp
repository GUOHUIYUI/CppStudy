#include <iostream>
#include <string>
#include <string_view>


enum class DeviceState {
	offline,
	idle,
	running,
	fault
};

class DeviceConfig {
public:
	bool SetName(std::string_view name)
	{
		if (name.size() < 1 || name.size() > 16)
		{
			return false;
		}
		name_ = name;
		return true;
	}
	const std::string& GetName()
	{
		return name_;
	}
	bool SetRate(int rate)
	{
		if (rate < 1 || rate > 1000)
		{
			return false;
		}
		sampleRate_ = rate;
		return true;
	}
	 int getRate()const
	{
		return sampleRate_;
	}
private:
	std::string name_{"dev"};
	int sampleRate_{100};
    DeviceState state_ { DeviceState::offline };
};
int main()
{
	//
	//验证合法修改、空名称、超长名称和采样率两个边界外值。
	DeviceConfig config;
    std::cout << config.SetName("") << ' '
        << config.GetName() << '\n';

    std::cout << config.SetName("12345678901234561") << ' '
        << config.GetName() << '\n';

    std::cout << config.SetRate(500) << ' '
        << config.getRate() << '\n';

    std::cout << config.SetRate(-1) << ' '
        << config.getRate() << '\n';
    std::cout << config.SetRate(1001) << ' '
        << config.getRate() << '\n';
	std::string str1{ "123" };
	


    return 0;
}
