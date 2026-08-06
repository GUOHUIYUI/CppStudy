#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

void report(int errorCode)
{
    std::cout << "errorCode:  " << errorCode << std::endl;
}

void report(const int* value)
{
    std::cout << (value==nullptr ? "no value" : "has value") << std::endl;
}



int main()
{
    report(0);
    report(nullptr);


    //练习
    int *Iptr{ nullptr };
    int a{ 1 };
    if (Iptr == nullptr)
    {
        Iptr = &a;
        std::cout << *Iptr << std::endl;
    }
    return 0;
}
