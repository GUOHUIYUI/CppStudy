#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
//函数重载 C++允许多个同名函数 可以通过参数列表的顺序，个数，类型区分 构成函数重载
//返回值类型不同无法构成重载

int maximum(int x, int y)
{
    return x > y ? x : y;
}

double maximun(double x, double y)
{
    return x > y ? x : y;
}


int main()
{
    maximum(1, 2);
    maximum(1.5, 1.5);//根据参数不同调用不同的函数
    

    return 0;
}
