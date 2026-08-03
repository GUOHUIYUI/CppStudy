#include<iostream>

struct Rectangle
{
	double length;
	double width;
};
//从参数看 area不会修改矩形对象本身
double area(const Rectangle& rect)
{
	//通过const引用传递参数可以避免复制对象的开销，同时也保证了函数内部不会修改传入的参数。
	return rect.length * rect.width;
}
//从参数看 scale会修改矩形对象本身
bool scale(Rectangle& rect, double factor)
{
	//通过引用传递参数可以避免复制对象的开销，同时也允许函数内部修改传入的参数。
	if (factor <= 0)
	{
		return false;
	}
	rect.length *= factor;
	rect.width *= factor;
	return true;
}




int main()
{
	struct Rectangle rect { 10, 5 };
	std::cout << "Area: " << area(rect) << std::endl;

	if(scale(rect, 2.0))
	{
		std::cout << "Scaled area: " << area(rect) << std::endl;
	}
    return 0;
}