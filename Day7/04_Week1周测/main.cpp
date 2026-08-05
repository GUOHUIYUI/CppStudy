#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

//1.安全读取double
bool readDouble(double &output)
{
    if (!(std::cin >> output))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

//2.交换两个int的引用函数:不用返回是因为可以通过引用直接修改原对象的值
void swapInt(int& num1, int& num2)
{
    int tmp = num1;
    num1 = num2;
    num2 = tmp;
}

/*
3.  下面哪些构成重载?
   1. int convert(int value);
   2. double convert(double value);
   3. double convert(int value);       // 与第一行的关系？
   4. int convert(int value, int base);
   1和2,4构成重载 1和2参数类型不同构成重载  1和4参数数量不同构成重载
   2和1,3,4 均构成重载  2和3参数类型不同   2和4参数类型和数量均不相同
   3和2,4 均构成重载  3和4参数类型和数量均不相同
   4和1,2,3 均构成重载  4和1,2,3 参数类型和数量均不相同
*/

//4. 写出一个合法的默认参数声明和非法的声明
    //func1是合法的，默认参数需要从右往左连续声明
    //func2是非法的
void func1(int a, int b=0);
//void func2(int a = 0, int b);

//5.写一个constexpr平方函数并使用static_assert验证
constexpr int square(int a)
{
    return a * a;
}
static_assert(square(6) == 36, "square fail");

/*
 6.  说明下面两个调用分别在何时计算。（1分）
    constexpr int a = square(4);  该函数在程序编译时计算
    int input{};
    std::cin >> input;
    int b = square(input);  在程序运行时调用计算
 */

/*7. 为“输入必须大于0”的函数设计三个测试，至少包含一个边界和一个非法输入。
        测试1：输入0
        测试2：输入-1
        测试3：输入100

*/
   




int main()
{
    return 0;
}
