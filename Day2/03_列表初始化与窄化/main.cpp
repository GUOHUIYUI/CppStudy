#include <iostream>


int main()
{
	//窄化是指将一个数据类型的值转换为另一个数据类型时，可能会丢失精度或范围的情况。
	double price{ 9.99 };
	int a = price;//允许转换，但是小数位置会丢失，发生窄化
	std::cout << "price: " << price << std::endl;//9.99
	std::cout << "a: " << a << std::endl;//9

	//int b{ price }; 列表初始化时会阻止明显的窄化转换，编译器会报错
	//如果需要进行窄化转换，可以使用static_cast<类型>(表达式) 明确表示需要转换并且愿意承担丢失精度
	int b{ static_cast<int>(price) };//可以转换会丢失精度
	std::cout << "b: " << b << std::endl;//9

	int c{ -1 };
	unsigned int d = c;//允许转换，但是会发生溢出，发生窄化 
	std::cout << "c: " << c << std::endl;//-1
	std::cout << "d: " << d << std::endl;//4294967295   变为极大值

	return 0;
}