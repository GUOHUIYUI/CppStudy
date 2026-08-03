#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


/*
	- 只改返回类型，误以为形成重载；
- 重载版本过多，导致隐式转换歧义；
- 默认参数不从右侧开始；
- 在函数声明和定义中重复指定默认值；
- 认为`inline`一定能提高性能；
- 认为`constexpr`函数不能接收运行时数据；
- 只写`constexpr`却不用`static_assert`验证。
*/

//默认参数与重载冲突
void print(int a)
{
	std::cout << abort << std::endl;
}

void print(int a, int b = 10)
{
	std::cout << a << std::endl;
}




int main()
{
	//print(1); 函数重载和默认参数冲突导致编译器不知道具体调用哪个函数
	return 0;
}
