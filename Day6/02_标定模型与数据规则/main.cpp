#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

inline bool isValid(double rawValue, double scale, double offset)
{
    return (rawValue<-100000||rawValue>100000||scale<0||scale>1000||offset<-100000||offset>100000) ? false:true;
}

constexpr double applyCalculate(double rawValue, double scale, double offset = 0.0)
{
    return rawValue * scale + offset;
}

static_assert(applyCalculate(100.0, 0.5, 2.0) == 52.0, "calibration failed");

int main()
{
    double rawValue{}, scale{}, offset{};
    std::cout << "input:" << std::endl;
    if (!(std::cin >> rawValue >> scale >> offset))
    {
        return false;
    }
    if (isValid(rawValue, scale, offset))
    {
        applyCalculate(rawValue,scale,offset);
    }
    else {
        std::cerr << "parameter error";
    }
    return 0;
}