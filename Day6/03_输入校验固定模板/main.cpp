#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

//std::cin>> 失败时，需要调用clear 和ignore函数  只调用clear只会清楚错误标志 只调用ignore只会清楚缓冲区错误数据  所以需要同时调用


//prompt是只读引用
bool readDouble(const std::string& prompt, double& value)
{
	std::cout << prompt;
	if (std::cin >> value)
	{
		return true;
	}
	std::cin.clear();
    //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return false;
}

//使用函数重载可以写出不同的版本
bool readValue(const std::string& prompt, double& value)
{
	std::cout << prompt;
	if (std::cin >> value)
	{
		return true;
	}
	std::cin.clear();
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return false;
}
bool readValue(const std::string& prompt, int& value)
{
	std::cout << prompt;
	if (std::cin >> value)
	{
		return true;
	}
	std::cin.clear();
	//std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return false;
}



int main()
{
	return 0;
}