#include <iostream>
#include "Pares.h"
int main()
{
    std::cout << "Hello, world!\n";
    const ParesResult result = paresRate("1001");

    if (!result.succeeded()) {
        std::cout << result.field << ": " << result.reason << '\n';
    }
  
    return 0;
}