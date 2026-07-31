#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";

	double celsius{};
    std::cout<<"请输入摄氏温度:";
	if (!(std::cin >> celsius))
	{
		std::cerr << "输入不是有效数字！" << std::endl;//使用std::cerr输出错误信息 比使用std::cout更合适 因为std::cerr是标准错误流
		return 1;
	}
	const double fahrenheit = (celsius * 9.0 / 5.0) + 32.0;

	std::cout<<"摄氏温度:"<<celsius<<" 对应的华氏温度是:"<<fahrenheit<<std::endl;

    return 0;
}