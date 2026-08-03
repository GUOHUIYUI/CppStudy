#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

double finalPrice(double price, int quantity = 1, double discount = 0.9)
{
	return price * quantity * discount;
}
//默认参数应该从右向左连续实现
//多文件编程时，默认值放在头文件声明处，定义处不重复书写

//是错误的
//double finalPrice(double price = 1, int quantity, double discount)
//{
//	return price * quantity * discount;
//}

int main()
{
	finalPrice(10);
	finalPrice(10, 20);
	finalPrice(10, 20, 0.5);
	return 0;
}
