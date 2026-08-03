#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
//constexpr 函数内部调用的所有函数，也必须是 constexpr
constexpr inline bool isValidOrder(double unitPrice,int quantity,double discount){
    if (unitPrice < 0 || quantity < 0 || quantity>100000 || discount < 0 || discount>1)
    {
        return false;
    }
    return true;
}

constexpr double finalPrice(double unitPrice, int quantity=1, double discount=1.0)
{
    if (!isValidOrder(unitPrice, quantity, discount))
    {
        return -1;
    }

    return unitPrice * quantity * discount;
}



int main()
{
    finalPrice(10.0);
    finalPrice(10.0, 3);
    finalPrice(10.0, 3, 0.8);
        
    return 0;
}
