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
    // ========== 编译期断言（至少 4 条）==========
    static_assert(maximum(3, 7) == 7, "MAX INT FAIL");
    static_assert(maximum(-2.5, -8.0) == -2.5, "MAX DOUBLE FAIL");
    static_assert(maximum(4, 4) == 4, "MAX EQUAL FAIL");
    static_assert(sum(1, 2) == 3, "SUM2 FAIL");       // ← 新增
    static_assert(sum(1, 2, 3) == 6, "SUM3 FAIL");       // ← 新增

    // ========== 运行时输入测试 ==========
    int a, b, c;
    double x, y;

    std::cout << "请输入两个整数（用于 maximum 和 sum）：";
    std::cin >> a >> b;

    std::cout << "maximum(" << a << ", " << b << ") = "
        << maximum(a, b) << std::endl;
    std::cout << "sum(" << a << ", " << b << ") = "
        << sum(a, b) << std::endl;

    std::cout << "请输入第三个整数（用于 sum 三参数版本）：";
    std::cin >> c;
    std::cout << "sum(" << a << ", " << b << ", " << c << ") = "
        << sum(a, b, c) << std::endl;

    std::cout << "请输入两个小数（用于 maximum double 版本）：";
    std::cin >> x >> y;
    std::cout << "maximum(" << x << ", " << y << ") = "
        << maximum(x, y) << std::endl;

    return 0;
}
