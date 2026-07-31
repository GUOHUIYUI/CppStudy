#include <iostream>


//'\n'和endl都可以实现换行，区别是endl还会强制刷新输出缓冲区
int main()
{
	std::cout << "Hello, world!\n";
	int score{ 25 };
	std::cout << "Score" << score << "\n";
	//  <<可以连续输出不同类型的数据
	std::cout << "name = " << "Alice"
		<< ", age = " << 20
		<< '\n';

	return 0;
}