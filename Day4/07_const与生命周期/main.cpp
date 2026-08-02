
/*
	const int*  指向常量的指针
	int* const  常量指针
*/







const int& broken()
{
	int x{ 10 };
	return x; //是错误的 因为x是局部变量 在函数返回后就会被销毁 所以返回的引用是悬空引用 const不影响对象的声明周期
}


int main()
{
	int x{ 10 };
	const int y{ 20 };
	const int& ref = x;//可以使用const引用指向普通变量
	//int& ref2 = y;//是错误的 因为y是常量 不能通过非常量引用修改常量的值
	//int& ref3 = 10;//是错误的 因为10是常量 不能通过非常量引用修改常量的值
	const int& ref3 = y;//是正确的 因为ref3是常量引用 可以指向常量
	const int& ref4 = 10;
	return 0;
}