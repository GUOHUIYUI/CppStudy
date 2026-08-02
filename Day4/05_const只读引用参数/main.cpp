#include<iostream>

void swap(int a, int b)
{
	int temp = a;
	a = b;
	b = temp;
}

void show(const int& a, const int& b)
{
	std::cout << "a: " << a << ", b: " << b << std::endl;
}

//使用值传递时，会复制一个对象的副本到函数参数中，对于一般的int 类型来说，复制的开销很小，一般使用值传递是可以接受的。
// 但是对于大型对象来说，复制的开销可能会很大。使用const引用传递参数可以避免这种开销，同时也保证了函数内部不会修改传入的参数。
int main()
{
    return 0;
}