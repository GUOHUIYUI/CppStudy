#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
//普通局部变量具有自动存储期。每次函数调用都会创建一个新的局部变量，当离开块作用域或函数结束时，该对象声明周期结束
//时间线processSample调用->raw创建->newNum创建->进入块中newNum1创建->输出newNum1，离开块->newNum1销毁->输出->newNum结束->raw结束->返回
void processSample(int raw)
{
    int newNum{ raw + 1 };
    {
        int newNum1{ newNum + 1 };
        std::cout << &newNum1 << "   " << newNum1 << "\n";

    }
    std::cout << &raw << "   " << raw << "\n";
    std::cout << &newNum << "   " << newNum << "\n";

}

int main()
{
    processSample(10);
    processSample(20);//每次调用时，之前的raw和newNum已经销毁,raw和newNum都是一个新的对象
    return 0;
}
