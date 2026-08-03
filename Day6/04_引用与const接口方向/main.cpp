#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>



// 前三个参数加不加const只影响函数内副本变量的属性，对外部调用对象均没有影响
// 引用增加const与否影响到外部调用者对象本身
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


int main()
{
    return 0;
}