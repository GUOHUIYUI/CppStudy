#include"example1.h"
#include <cstdint>
#include <iostream>
#include <string_view>


//访问枚举值时必须加作用域
//定义两个值一样的宏，编译器无法阻止混用，enum class把类别也放进类型中
int main()
{
    DeviceStatus state(DeviceStatus::idle);
    DeviceStatus1 state1(DeviceStatus1::stopping);
    std::cout << toString(state) << "\n";
    std::cout << toString(state1) << "\n";

    return 0;
}
