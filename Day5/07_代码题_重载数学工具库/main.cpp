#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

//constexpr表示函数可以在编译期计算   两个函数依据参数列表数据类型不同实现函数重载

constexpr int maximum(int left, int right)
{
    return left > right ? left : right;
}

constexpr double maximum(double left, double right)
{
    return left > right ? left : right;

}

//两个函数依据参数个数不同构成函数重载
constexpr int sum(int a, int b)
{
    return a + b;
}

constexpr int sum(int a, int b, int c)
{
    return a + b + c;
}



int main()
{
    static_assert(maximum(3, 7) == 7, "MAX FAIL");
    static_assert(maximum(-2.5, -8.0) == -2.5, "MAX FAIL");
    static_assert(maximum(4, 4) == 4, "MAX FAIL");
    sum(1, 2);
    sum(1, 2, 3);
    return 0;
}
