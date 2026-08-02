#include <iostream>
int main()
{
    int a{ 10 };
	int& ref = a; // ref是a的引用
    
    int b{ 20 };
	ref = b; // 这里是将b的值赋给a，而不是让ref指向b
    
    return 0;
}