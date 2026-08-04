#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

int main()
{
    int nums[10]{ 0 };
    //错误 ，value实际是nums中的元素
    //for (int value : nums)
    //{
    //    std::cout << nums[values];
    //}
    for (int value : nums)
    {
        std::cout << value << std::endl;
    }
    return 0;
}
