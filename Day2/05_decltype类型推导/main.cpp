#include <iostream>


int main()
{
	int price{ 10 };
	decltype(price) price2{ 20 }; // decltype(price）返回int类型

	double price3{ 30.5 };
	decltype(price3) price4{ 40.5 }; //price4的类型是double

	int price5{ 50 };
	decltype(price5 + 1) price6{ 60 }; //decltype(price5 + 1)不会执行price5 + 1，price6的类型是int

	return 0;
}