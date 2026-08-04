#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

constexpr bool isCalibrationValid(double rawValue, double scale, double offset)
{
	if (rawValue < -100000 || rawValue>100000)
	{
		return false;
	}
	if (scale <= 0 || scale > 1000)
	{
		return false;
	}
	if (offset < -100000 || offset>100000)
	{
		return false;
	}
	return true;

}

constexpr double applyCalibration(double rawValue, double scale, double offset)
{
	return rawValue * scale + offset;
}

bool calibrate(double rawValue, double scale, double offset, double &result)
{
	if (!isCalibrationValid(rawValue, scale, offset))
	{
		std::cout << "parameter ERROR" << std::endl;
		return false;
	}
	result = applyCalibration(rawValue, scale, offset);
	return true;
}

bool calibrate(int rawValue, double scale, double offset, double &result)
{
	return calibrate(static_cast<double>(rawValue), scale, offset, result);
}

int main()
{
	return 0;
}
