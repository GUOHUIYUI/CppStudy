#include <iostream>


bool divide(int a, int b, int& quotient,int& remainder) //引用传递
{
	if (b == 0)
	{
		return false; //除数为0，返回false
	}
	quotient = a / b; //将商赋值给引用参数quotient
	remainder = a % b; //将余数赋值给引用参数remainder
	return true; //返回true表示成功
}




int main()
{
	int quotient{};
	int remainder{};
	divide(10, 20, quotient, remainder);
	std::cout << "Quotient: " << quotient << std::endl;
	std::cout << "Remainder: " << remainder << std::endl;

    return 0;
}