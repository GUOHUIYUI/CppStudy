#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// 构成重载 参数个数不同 参数类型不同  返回值不同无法构成重载
//double func1(int a)
//{
//    return a;
//}

int func1(int a)
{
    return a;
}

int func1(int a, int b)
{
    return a + b;
}

double func1(double a)
{
    return a;
}




int main()
{
    return 0;
}
