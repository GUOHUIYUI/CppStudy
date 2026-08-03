#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
//通过修改函数参数的类型即可提供函数重载
bool calibrate(
    double rawValue,
    double scale,
    double offset,
    double& calibratedValue
)
{
    if (rawValue < -100000.0 || rawValue > 100000.0)
    {
        return false;
    }

    if (scale <= 0.0 || scale > 1000.0)
    {
        return false;
    }

    if (offset < -100000.0 || offset > 100000.0)
    {
        return false;
    }
    calibratedValue = rawValue * scale + offset;
    return true;
}

bool calibrate(
    int rawValue,
    double scale,
    double offset,
    double& calibratedValue
)
{
    if (rawValue < -100000 || rawValue > 100000)
    {
        return false;
    }

    if (scale <= 0.0 || scale > 1000.0)
    {
        return false;
    }

    if (offset < -100000.0 || offset > 100000.0)
    {
        return false;
    }
    calibratedValue = rawValue * scale + offset;
    return true;
}

int main()
{
    double value{};
    calibrate(1000.0, 1.0, 1.0, value);
    calibrate(1000, 1.0, 1.0, value);//分别调用两个不同实现的函数
    return 0;
}