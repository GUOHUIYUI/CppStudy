#include <stdexcept>
#include<string>
#include<utility>
#include<iostream>
class DeviceConfig {
public:
	DeviceConfig(std::string name, int rate)
		:name_{std::move(name)},rate_{rate}
	{
		if (name_.empty() || name_.size() > 16)
		{
			throw std::invalid_argument{ "invalid_argument" };
		}
		if (rate_ < 1 || rate_>1000)
		{
			throw std::invalid_argument{ "rate must be 1 to 1000" };
		}
	}
	const std::string& name() const { return name_; }
	int rate() const { return rate_; }

private: 
	std::string name_;
	int rate_;
};

int main()
{
	try {
		DeviceConfig config{ "sensor-a",100 };
		std::cout << config.name() << '\n';
	}
	catch (const std::invalid_argument& error)
	{
		std::cout << error.what() << '\n';
	}
	try {
		DeviceConfig config1{ "",100 };
		std::cout << config1.name() << '\n';
	}
	catch (const std::invalid_argument& error)
	{
		std::cout << error.what() << '\n';
	}
	try {
		DeviceConfig config2{ "sensor-a",0 };
		std::cout << config2.name() << '\n';
	}
	catch (const std::invalid_argument& error)
	{
		std::cout << error.what() << '\n';
	}
	try {
		DeviceConfig config3{ "sensor-a",10000 };
		std::cout << config3.name() << '\n';
	}
	catch (const std::invalid_argument& error)
	{
		std::cout << error.what() << '\n';
	}

}
