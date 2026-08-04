#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

constexpr  int isCalibrationValid(double rawValue, double scale, double offset)
{
	int num{};
	if (rawValue < -100000 || rawValue>100000)
	{
		num |= 1 << 0;
	}
	if (scale <= 0 || scale > 1000)
	{
		num |= 1 << 1;
	}
	if (offset < -100000 || offset>100000)
	{
		num |= 1 << 2;
	}

	return  num;
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
	int num = isCalibrationValid(rawValue, scale, offset);
	if (!(num == 0))
	{
		if (num & 1 << 0)
		{
			std::cerr << "rawValue error" << std::endl;
		}
		if (num & 1 << 1)
		{
			std::cerr << "scale error" << std::endl;
		}
		if (num & 1 << 2)
		{
			std::cerr << "offset error" << std::endl;
		}
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
		std::cerr << "input ERROR" << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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