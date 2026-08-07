#include <array>
#include <cstddef>
#include <iostream>



int replaceNegatives(std::array<int, 6> &values);
int main()
{
    std::array<int, 6> values{ 4, -2, 7, -1, 0, 5 };
    std::array<int, 6> values1{ 4, 2, 7, 1, 0, 5 };
    std::array<int, 6> values2{ 4, -2, 7, -1, 0, 5 };


    int recv{};
    recv = replaceNegatives(values);
    for (int value : values)
    {
        std::cout << value << "  " << std::endl;
    }
    std::cout << "replaced:  " << recv << std::endl;

    return 0;
}

/*
要求：
- 把所有负数替换为0；
- 返回被替换的元素数量；
- 使用范围`for`和引用修改元素；
- 在main()中输出返回值和修改后的数组。
*/
int replaceNegatives(std::array<int, 6> &values)
{
    int replaced{};
    for(int& value:values)
    {
        if (value < 0)
        {
            value = 0;
            replaced++;
        }
    }
    return replaced;
}