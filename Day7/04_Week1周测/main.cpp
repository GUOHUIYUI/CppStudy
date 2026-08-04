#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

//1.安全读取double
bool readDouble(double &output)
{
    if (!(std::cin >> output))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}



int main()
{
    return 0;
}
