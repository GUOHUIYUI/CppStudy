#include<windows.h>
#include<iostream>


/*
读取一个非负的`long long`总秒数，将它分解成天、小时、分钟和秒。

要求：

- 输入失败或输入负数时结束程序；
- 使用整数除法和取余；
- 使用列表初始化；
- 使用`decltype`声明至少一个与总秒数类型相同的变量。
*/


int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	long long totalSeconds{};
	if (!(std::cin >> totalSeconds) || totalSeconds < 0)
	{
		std::cerr << "输入错误" << std::endl;
		return 1;
	}
	decltype(totalSeconds) days{ totalSeconds / (24 * 60 * 60) };
	decltype(totalSeconds) hours{ totalSeconds % (24 * 60 * 60) / (60 * 60) };
	decltype(totalSeconds) minutes{ totalSeconds % (60 * 60) / 60 };
	decltype(totalSeconds) seconds{ totalSeconds % 60 };
	std::cout << "天: " << days << std::endl;
	std::cout << "小时: " << hours << std::endl;
	std::cout << "分钟: " << minutes << std::endl;
	std::cout << "秒: " << seconds << std::endl;


    return 0;
}