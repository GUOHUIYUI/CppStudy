#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
//constexpr函数在满足条件是可以在编译器求值
// constexpr表示允许在编译期计算，不表示所有调用都强制发生在编译期


constexpr int square(int value)
{
    return value * value;
}

int square1(int value)
{
    return value * value;
}

constexpr int isValid(bool value)
{
    return value;
}


int main()
{
    // static_assert(square(4) == 25, "square calculate failed"); 静态断言错误 square函数在编译期求值
    int input{};
    std::cin >> input;
    square(input);//此次调用发生在运行时，所以是在运行时完成。

    static_assert(isValid(true), "false");

    return 0;
}
