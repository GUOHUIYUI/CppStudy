#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
/*  
    存储期             典型声明                    存在时间
    自动存储期         普通变量                     随块作用域存在，离开作用域时销毁
    静态存储期         全局变量和静态局部变量       在整个程序执行期间存在
    线程存储期         thread_local对象             每个线程各有一份，随线程存在
    动态存储期         使用new后获得的对象           由程序员手动销毁释放

    基础类型看不出销毁操作，对象会在销毁时调用析构函数


  */

int main()
{
    return 0;
}
