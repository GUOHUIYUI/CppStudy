#include <iostream>

int main()
{
	//引用是别名 引用初始化时必须绑定到一个对象上，引用一旦被初始化后，就不能再指向其他对象
	int score{ 10 };
	std::cout << score << std::endl;
	int& ref = score; 
	std::cout << ref << std::endl;
	ref = 20;
	std::cout << score << std::endl;
	std::cout << ref << std::endl;
	std::cout << &score << std::endl;
	std::cout << &ref << std::endl;


	//int& a; 不能创建引用而不初始化



	return 0;
}