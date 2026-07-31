#include <iostream>

int main()
{
	std::cout << "Hello, world!\n";
	double num1{}, num2{};
	char operation{};

	std::cout << "请输入第一个数字:";
	if (!(std::cin >> num1))
	{
		std::cerr << "输入不是有效数字！" << std::endl;
	}
	std::cout << "请输入运算符(+,-,*,/):";
	if (!(std::cin >> operation) || (operation != '+' && operation != '-' && operation != '*' && operation != '/'))
	{
		std::cerr << "输入不是有效字符！" << std::endl;
		return 1;
	}

	std::cout << "请输入第二个数字:";
	if (!(std::cin >> num2))
	{
		std::cerr << "输入不是有效数字！" << std::endl;
		return 1;
	}
	switch (operation)
	{
	case '+':
		std::cout << "结果: " << num1 + num2 << std::endl;
		break;
	case '-':
		std::cout << "结果: " << num1 - num2 << std::endl;
		break;
	case '*':
		std::cout << "结果: " << num1 * num2 << std::endl;
		break;
	case '/':
		if (num2 != 0)
		{
			std::cout << "结果: " << num1 / num2 << std::endl;
		}
		else
		{
			std::cerr << "错误：除数不能为零！" << std::endl;
			return 1;
		}
		break;
	default:
		std::cerr << "错误：无效的运算符！" << std::endl;
		return 1;
	}

	return 0;
}