#include <iostream>


//auto 让编译器根据初始化表达式的类型自动推导变量的类型


int main()
{
	auto a = 10; // a 的类型被推导为 int
	auto b = 1.0; // b 的类型被推导为 double
	auto c = 'a'; // c 的类型被推导为 char
	auto d = "hello"; // d 的类型被推导为 const char*

	//auto不代表是动态类型，数据类型仍然在编译时确定，auto只是让编译器根据初始化表达式的类型自动推导变量的类型。

	auto e = 10;
	e = 20;
	//e = "abd"; 错误
	/*
		适合auto的场景
		1. 变量类型复杂，难以书写
		2. 右侧已经明确清楚类型
		3. 不希望重复书写类型
	*/

	//auto result = calculate();  不适合不明确函数返回值类型 会造成程序阅读困难


    return 0;
}