#include <iostream>

//命名空间：主要用于避免名称冲突

//全引用 不建议大型项目头文件中使用
//using namespace std;

//单项引用
using std::cout;
using std::cin;
using std::endl;


int main()
{
    cout << "Hello, world!\n";

    return 0;
}