#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

//int &process1()
//{
//    int num{ 1 };//返回局部变量的地址或引用
//    //进入process1时创建num，离开process1时销毁num  所以造成悬空引用
//    return num;
//}
//
//int *process2()
//{
//    int num{ 1 };//返回局部变量的地址或引用
//    //进入process1时创建num，离开process1时销毁num  所以造成指针指向已销毁的地址，访问会导致未定义行为
//    return &num;
//}
//void process3(int num)
//{
//    {
//        int num{ 2 };
//        num = 3;  //因为变量遮蔽，就近原则，导致实际修改的为{}内的num变量
//    }
//}
//
//void process4()
//{
//    int num;
//    std::cout << num << std::endl;//访问未初始化的变量，会造成未定义行为
//}
//
//void process5(int &num)
//{
//    //初次调用process5时创建num1，直到整个程序结束时销毁
//    static int num1{ 3 };//本意为每次调用时将传入参数+3，但实际static局部变量并不会每次销毁，所以导致实际运行和预期不符
//    num1 += num;
//    num = num1;
//}

//修正
int process1()
{
	int num{ 1 };
	return num;
}

int process2()
{
	int num{ 1 };
	return num;
}
void process3(int& num)
{
	num = 3;
}

int process4()
{
	int num{};
	return num;
}

void process5(int &num)
{

	int num1{ 3 };
	num1 += num;
	num = num1;
}

void check(const std::string &str, int expect, int actual)
{
	std::cout
		<< str
		<< " | actual=" << actual
		<< " expected=" << expect
		<< (actual == expect ? " | PASS\n" : " | FAIL\n");
}



int main()
{
	//原错误：返回局部引用
	int num{ process1() };
    check("process1", 1, num);

	//原错误：返回局部对象指针
	num = process2();
    check("process2", 1, num);

	//原错误：局部变量遮蔽
    process3(num);
    check("process3", 3, num);

	//原错误：访问未初始化变量
    num=process4();
    check("process4", 0, num);

    //原错误：static局部变量
	num = 0;
    process5(num);
    check("process5", 3, num);
	num = 0;
	process5(num);
	check("process5", 3, num);

	return 0;
}
