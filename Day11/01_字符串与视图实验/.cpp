#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

//std::string 负责保存字符序列，可以直接复制，比较，拼接，赋值

void example1();
void test1();



int main()
{
    //C字符串的边界来自终止字符
    //数组的长度是4 文本长度是3 
    //因为许多C字符串函数会一直读取，直到读到'\0'，遗漏终止字符可能导致越界读取
    char command[] = { 'R','U','N','\0' };
    example1();
    test1();
    return 0;
}
void example1()
{
    char command[8]{ "RUN" };
    //sizeof 回答数组占据多少字节   strlen回答第一个'\0'之前有多少字符
    cout << "capacity: " << sizeof(command) << endl;  //8
    cout << "length: " << strlen(command) << endl;     //3
}

void test1()
{
    char command[8]{ "STATUS" };
    //因为sizeof回答的是数组占据多少字节，和字符长度无关
    cout << "capacity: " << sizeof(command) << endl;  //8
    cout << "length: " << strlen(command) << endl;     //6
}