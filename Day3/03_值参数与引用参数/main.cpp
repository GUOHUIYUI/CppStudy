#include<iostream>


//值传递传递的是变量的副本  在函数内修改副本不会影响原来的变量
//引用传递传递的是变量的别名  在函数内修改别名会影响原来的变量

void resetByref(int& ref) //引用传递
{
	ref = 0;
}

void resetByvalue(int value) //值传递
{
	value = 0;
}

int main()
{
	int a{ 10 };
	resetByvalue(a); //值传递
	std::cout << a << std::endl; //输出10

	int& ref = a; //引用传递
	resetByref(ref); //引用传递
	std::cout << a << std::endl; //输出0
    return 0;
}