#include <iostream>


//int age{};{}是c++统一的初始化语法   可以使用{}来初始化任何类型的变量  使用未初始化的变量会导致未定义行为
//{}也可以附带初始值 例如int age{10};

//cin返回值  true表示输入成功  false表示输入失败
int main()
{
	std::cout << "Hello, world!\n";
	int age{};

	//std::cout << "请输入年龄：";
	//if (!(std::cin >> age))
	//{
	//	std::cout << "输入不是有效整数！" << std::endl;
	//	return 1;
	//}
	while (true)
	{
		std::cout << "请输入年龄：";
		if (std::cin >> age && age >= 0 && age <= 100)
		{
			break; // 输入成功，跳出循环
		}
		else
		{
			std::cout << "输入不是有效整数！请重新输入。" << std::endl;
			std::cin.clear(); // 清除错误标志
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略错误输入
		}
	}
	std::cout << "年龄是：" << age << std::endl;


	return 0;
}