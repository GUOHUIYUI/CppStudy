#include <iostream>
#include"limited_counter.h"
int main()
{
    std::cout << "Hello, world!\n";
    LimitCounter counter;
    counter.increament();
    std::cout << counter.value() << "\n";
    return 0;
}