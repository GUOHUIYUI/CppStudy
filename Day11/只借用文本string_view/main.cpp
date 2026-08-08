#include <cstring>
#include <iostream>
#include <string>
#include <string_view>
#include<windows.h>

using namespace std;

//std::string_view 视图保存的是字符的位置和长度，不拥有字符  视图不能指向比自己活的短的视图  适合用于只读判断
//它可以查看字符串字面量、字符数组或仍然存活的`std::string`。适合“函数只读，而且不需要保存参数”的接口。
bool isKnowCommand(std::string_view str_view)
{
	return str_view == "RUN" || str_view == "STOP" || str_view == "STATUS";
}

bool hasPrefix(std::string_view text, std::string_view prefix);

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	std::string str{ "RUN" };
	std::cout << isKnowCommand(str) << std::endl;
	
	std::cout << std::boolalpha;
	std::cout << "空前缀:       " << hasPrefix("hello", "") << "\n"; // true
	std::cout << "相等字符串:   " << hasPrefix("hello", "hello") << "\n"; // true
	std::cout << "前缀过长:     " << hasPrefix("hi", "hello") << "\n"; // false
	std::cout << "正常匹配:     " << hasPrefix("hello", "hel") << "\n"; // true
	std::cout << "前缀不匹配:   " << hasPrefix("hello", "hex") << "\n"; // false
	return 0;
}

bool hasPrefix(std::string_view text, std::string_view prefix)
{
	if (text.size() < prefix.size())
	{
		return false;
	}
	std::string tmp{ text.substr(0,prefix.size()) };
	return tmp == prefix;
}