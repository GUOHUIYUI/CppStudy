#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

using namespace std;

void textCount(std::string_view str)
{
    int space{}, num{};
    std::cout << "strCount:  " << str.size() << std::endl;
    for (char value : str)
    {
        if (value == ' ')
        {
            space++;
            continue;
        }
        if (value >= '0' && value <= '9')
        {
            num++;
        }
    }
    std::cout << "spaceCount: " << space << std::endl;
    std::cout << "numCount: " << num << std::endl;
}


int main()
{
    std::string str{ "123 456 789" };
    textCount(str);
    std::string str1{ "         " };
    textCount(str1);
    std::string str2{ "dawhdjwa123 " };
    textCount(str2);

    return 0;
}
