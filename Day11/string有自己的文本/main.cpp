#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;


void example1();


//std::string 负责保存字符序列，可以直接复制，赋值，比较和拼接
int main()
{
    std::string command{ "SET" };
    command += " RATE";
    command += " 100";

    std::cout << "length:  " << command.size() << std::endl;
    std::cout << command << std::endl;
    std::cout << std::boolalpha << (command == "SET RATE 100") << std::endl;
    //常用操作
    std::cout << command.find('S')<<std::endl;//查找指定字符串，查找到返回下标，查找不到返回`std::string::npos` 不能将查找不到认为下标0
    std::cout << command.empty() << std::endl;//判定字符串是否为空 空返回true  非空返回false
    std::cout << command.size() << std::endl;   //返回字符串长度
    std::cout << command.substr(0,3) << std::endl; //截取字符串  从第一个参数起，截取第二个参数长度的字符串

    example1();


    return 0;
}
void example1()
{
    const std::string line{ "MODE AUTO" };
    const std::size_t separator{ line.find(' ') };
    if (separator == std::string::npos)
    {
        std::cout << "only command\n";
        return;
    }
    const std::string name{ line.substr(0,separator) };
    const std::string argumen{ line.substr(separator+1) };
    std::cout << "name:  " << name << std::endl;
    std::cout << "argumen:  " << argumen << std::endl;



}

