#include<iostream>


struct Rectangle {
    double width;
    double height;
};

bool isValid(const Rectangle& rect)
{
    return rect.width > 0 && rect.height > 0;
}

double perimeter(const Rectangle& rect)    //无需修改对象的参数所以使用const引用可以减少对象复制的开销 又可以避免修改对象本身
{
    return (rect.width + rect.height) * 2;
}

bool resize(Rectangle& rect,double width,double height) //因为要修改对象的参数 所以使用普通引用
{
    if (width <= 0 || height <= 0)
    {
        return false;
    }
    rect.height = height;
    rect.width = width;
    return true;
}



int main()
{
    
    return 0;
}