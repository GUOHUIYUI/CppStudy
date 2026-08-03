#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
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

inline bool isValid(double rawValue, double scale, double offset)
{
	return (rawValue < -100000 || rawValue>100000 || scale <= 0 || scale>1000 || offset < -100000 || offset>100000) ? false : true;
}

constexpr double applyCalculate(double rawValue, double scale, double offset = 0.0)
{
	return rawValue * scale + offset;
}

void checkEqual(bool isValid)
{
	if (isValid)
	{
		std::cout << "PASS" << std::endl;
		
	}else
	{
        std::cout << "FAIL" << std::endl;
    }



}

int main()
{
	checkEqual(isValid(100, 0.5, 2));
	checkEqual(isValid(0, 1, 0));
	checkEqual(isValid(-100000, 1, 0));
	checkEqual(isValid(100000, 1, 0));
	checkEqual(isValid(100001, 1, 0));
	checkEqual(isValid(100, 0, 0));
	checkEqual(isValid(100, 100, -100000));
	//checkEqual(isValid(100, 0.5, 0));
    return 0;
}