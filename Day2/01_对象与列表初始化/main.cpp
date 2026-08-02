#include <iostream>




int main()
{
	//只声明未初始化的变量，操作会出现未定义行为
	int a;
	char b;
	// std::cout << "a: " << a << std::endl; 未定义行为
	// std::cout << "b: " << b << std::endl;
	//显示建立初始化
	//使用大括号会给变量一个默认值，避免未定义行为
	int c{};
	double d{};
	bool e{};
	char f{};
	std::cout << "c: " << c << std::endl;//0
	std::cout << "d: " << d << std::endl;//0.0
	std::cout << "e: " << e << std::endl;//false
	std::cout << "f: " << f << std::endl;//空字符

	//也可直接赋值初始化
	int g{ 1 };
	double h{ 2.1 };
	bool i{ true };
	char j{ 'a' };
	std::cout << "g: " << g << std::endl;
	std::cout << "h: " << h << std::endl;
	std::cout << "i: " << i << std::endl;
	std::cout << "j: " << j << std::endl;




	return 0;
}
