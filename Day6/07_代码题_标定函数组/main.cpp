#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
constexpr bool isCalibrationValid(double rawValue, double scale, double offset)
{
	return (rawValue < -100000 || rawValue>100000 || scale <= 0 || scale > 1000 || offset < -100000 || offset>100000) ? false : true;
}

constexpr double applyCalibration(double rawValue, double scale, double offset = 0.0)
{
	return rawValue * scale + offset;
}

bool calibrate(
    double rawValue,
    double scale,
    double offset,
    double& calibratedValue
)
{
    if (!isCalibrationValid(rawValue, scale, offset))
    {
        return false;
    }
    calibratedValue= applyCalibration(rawValue,scale,offset);
    return true;
}
bool calibrate(
    int rawValue,
    double scale,
    double offset,
    double& calibratedValue
)
{
    return calibrate(static_cast<double>(rawValue), scale, offset, calibratedValue);
}
static_assert(
    isCalibrationValid(0.0, 1.0, 0.0),
    "normal value should be valid");

static_assert(
    isCalibrationValid(-100000.0, 0.1, 100000.0),
    "boundary value should be valid");

static_assert(
    !isCalibrationValid(100001.0, 1.0, 0.0),
    "rawValue out of range should be invalid");

static_assert(
    !isCalibrationValid(0.0, 0.0, 0.0),
    "scale must be greater than zero");

static_assert(
    applyCalibration(100.0, 0.5, 2.0) == 52.0,
    "formula test failed");


int main()
{
    return 0;
}