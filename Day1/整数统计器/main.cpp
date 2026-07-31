#include <iostream>

int main()
{
	std::cout << "Hello, world!\n";
	int max{}, min{}, sum{};
	double average{};
	int num_count{};
	std::cout << "请输入整数的个数:";
	if (!(std::cin >> num_count))
	{
		std::cerr << "输入不是有效整数！" << std::endl;
		return 1;
	}
	for (int i = 0; i < num_count; ++i)
	{
		int num{};
		std::cout << "请输入第" << (i + 1) << "个整数:";
		if (!(std::cin >> num))
		{
			std::cerr << "输入" << i << "个不是有效整数！" << std::endl;
			return 1;
		}
		if (i == 0)
		{
			max = num;
			min = num;
		}
		else {
			if (num > max)
			{
				max = num;
			}
			if (num < min)
			{
				min = num;
			}
		}
		sum += num;
	}
	//average = (double)sum / num_count;
	average = static_cast<double>(sum) / num_count;//使用static_cast进行类型转换
	std::cout << "最大值: " << max << std::endl;
	std::cout << "最小值: " << min << std::endl;
	std::cout << "总和: " << sum << std::endl;
	std::cout << "平均值: " << average << std::endl;

	


	return 0;
}