#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

//花括号形成块作用域，花括号内的可以访问括号外的对象，括号外的无法访问括号内的对象，内层声明同名对象会遮蔽外层对象。就近原则
//batchSampleCount的作用域就在{}内部，程序进入内层块时创建batchSampleCount 离开时销毁



int main()
{
    int totalSampleCount{ 10 };
    {
        int batchSampleCount{ 3 };
        std::cout << batchSampleCount << "\n";
    }
    std::cout << totalSampleCount << "\n";
    //int totalSampleCount{ 10 };
    //{
    //    int totalSampleCount{ 3 };
    //    std::cout << totalSampleCount << "\n";//3  “totalSampleCount”的声明隐藏了上一个本地声明
    //}
    //std::cout << totalSampleCount << "\n";//10


    return 0;
}
