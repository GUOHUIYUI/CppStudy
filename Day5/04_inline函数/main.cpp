#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

//可以将函数在调用处展开
//是否真正内敛是编译器的优化决定

//内联函数
inline bool isValid(int a)
{
    return a > 0;
}


int main()
{
    return 0;
}
