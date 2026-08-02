#include<windows.h>
#include <iostream>

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	double price{};
	int quantity{};
	if (!(std::cin >> price) || price < 0)
	{
		std::cout << "输入单价错误" << std::endl;
		return 1;
	}
	if (!(std::cin >> quantity) || quantity < 0)
	{
		std::cout << "输入数量错误" << std::endl;
		return 1;
	}

	const auto total{ price * quantity };
	decltype(price)discountTotal{ total };
	if (total > 100)
	{
		discountTotal = total * 0.9;
	}
	std::cout << "总价: " << total << std::endl;
	std::cout << "折扣后总价: " << discountTotal << std::endl;
	return 0;
}