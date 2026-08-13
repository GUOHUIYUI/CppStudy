#include <iostream>


//`::`是作用域解析运算符。`metric::convert`明确表示“命名空间`display`里的`convert`”，而不是把所有名字重新变得独一无二。
namespace metric {
    double convert(double value)
    {
        return value * 1000.0;
    }
}

namespace display {
    int convert(double value)
    {
        return static_cast<int>(value);
    }
}


//练习1：建立`temperature`和`distance`两个命名空间，各自定义一个`toBaseUnit(double)`函数。调用时保留完整限定名，并解释为什么函数名相同仍能共存。
namespace temperature {
    double toBaseUnit(double value)
    {
        return value * 1.8 + 32;
    }
}

namespace distance {
    double toBaseUnit(double value)
    {
        return value * 100;
    }
}


//namespace device::config {            等价于 namespace device{               使用时;device::config::DeviceConfig config
//    class DeviceConfig {                      namespace config{
//        //...                                     //..
//    };                                            }
//}                                                  }       

int main()
{
    std::cout << "Hello, world!\n";
    std::cout << metric::convert(1.5) << '\n';//分别使用不同命名空间中的函数
    std::cout << display::convert(1.5) << '\n';
    std::cout << temperature::toBaseUnit(32) << '\n';//因为它们的命名空间不同，相互独立
    std::cout << distance::toBaseUnit(32) << '\n';

    return 0;
}