#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
//静态局部变量的作用域仍然是在花括号内，但是其生命周期从第一次初始化时开始，一直到整个程序结束时销毁，所以可以保存上次状态
//thread_local int errorCount{};表示每个线程各有一份计数器  它既不是所有线程共享的计数器，也不是每次函数调用都重建的局部计数器
void process()
{
    static int num{};//若删除static，则每次调用都会创建新的局部变量
    num++;
    std::cout << num << "\n";
}


int main()
{
    process();//1
    process();//2
    process();//3

    return 0;
}
