#include <iostream>


void swapByref(int& a,int& b) //引用传递
{
	int temp = a;
	a = b;
	b = temp;
}

void swapByvalue(int a, int b) //值传递
{
	int temp = a;
	a = b;
	b = temp;
}


int main()
{
	int x{ 5 };
	int y{ 10 };
	std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
	swapByref(x, y);//引用传递交换ab的值
	std::cout << "After swap: x = " << x << ", y = " << y << std::endl;

	int c{ 15 };
	int d{ 20 };
	std::cout << "Before swap: c = " << c << ", d = " << d << std::endl;
	swapByvalue(c, d); //值传递交换ab的值 交换的只是变量副本的值，对变量本身没有影响
	std::cout << "After swap: c = " << c << ", d = " << d << std::endl;	
    return 0;
}