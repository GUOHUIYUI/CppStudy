#include<windows.h>
#include <iostream>

/*
读取商品单价、数量和折扣率，输出原价及折后价。

要求：

- 单价不能为负；
- 数量必须为`0～100000`的整数；
- 折扣率必须处于`0～1`；
- 使用`{}`初始化所有变量；
- 至少使用一次合理的`auto`；
- 结果使用`double`计算。
*/

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	double price{};
	int quantity{};
	double discountRate{};
	if (!(std::cin >> price) || price < 0)
	{
		std::cerr << "输入单价错误" << std::endl;
		return 1;
	}
	if (!(std::cin >> quantity) || quantity < 0 || quantity > 100000)
	{
		std::cerr << "输入数量错误" << std::endl;
		return 1;
	}
	if (!(std::cin >> discountRate) || discountRate < 0 || discountRate > 1)
	{
		std::cerr << "输入折扣率错误" << std::endl;
		return 1;
	}

	const auto total{ price * quantity };
	decltype(total) discountTotal{ total * discountRate };

	std::cout << "总价: " << total << std::endl;
	std::cout << "折扣后总价: " << discountTotal << std::endl;





    return 0;
}