#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

constexpr  bool isCalibrationValid(double rawValue, double scale, double offset)
{
	bool flag{ true };
	if (rawValue < -100000 || rawValue>100000)
	{
		std::cout << "rawValue ERROR" << std::endl;
		flag = false;
	}
	if (scale <= 0 || scale>1000)
	{
		std::cout << "scale ERROR" << std::endl;
		flag = false;
	}
	if (offset < -100000 || offset>100000)
	{
		std::cout << "offset ERROR" << std::endl;
		flag = false;
	}

	return  flag;
}

constexpr double applyCalibration(double rawValue, double scale, double offset = 0.0)
{
	return rawValue * scale + offset;
}

bool calibrate(
	double rawValue,
	double scale,
	double offset,
	double &calibratedValue
)
{
	if (!isCalibrationValid(rawValue, scale, offset))
	{
		return false;
	}
	calibratedValue = applyCalibration(rawValue, scale, offset);
	return true;
}
bool calibrate(
	int rawValue,
	double scale,
	double offset,
	double &calibratedValue
)
{
	return calibrate(static_cast<double>(rawValue), scale, offset, calibratedValue);
}

bool inputFunc(double &rawValue, double &scale, double &offset)
{
	if (!(std::cin >> rawValue >> scale >> offset))
	{
		std::cerr << "input ERROR"<<std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		return false;
	}
	return true;
}

void check(double &rawValue, double &scale, double &offset, double &calibratedValue)
{
	if (!inputFunc(rawValue, scale, offset))
	{
		return;
	}
	if (!calibrate(rawValue, scale, offset, calibratedValue))
	{
		return;
	}
	
	std::cout << "rawValue:" << rawValue << "scale:" << scale << "offset:" << offset << "calibratedValue:" << calibratedValue << std::endl;

}

int main()
{
	double rawValue{}, scale{}, offset{}, calibratedValue{};
	check(rawValue, scale, offset, calibratedValue);
	
	return 0;
}