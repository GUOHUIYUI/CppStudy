#include <iostream>
#include <stdexcept>

//构造函数没有返回值，void也不能xie
//成员按照声明时的顺序进行初始化，不按初始化列表顺序进行初始化
//不要先创建明显非法对象，再期待调用者记得补全全部字段
//不要为普通成员编写空的或重复清理的析构函数

class TemperatureRange {
public:
    TemperatureRange(int low,int high)
        :low_{low},
        high_{high}
    {
        if (low_ > high_)
        {
            throw std::invalid_argument{ "low must be <= high" };
        }
   }
    int high()const { return high_; }
    int low()const { return low_; }

private:
    int low_;
    int high_;
};



int main()
{
    try {
        TemperatureRange temp{ 100,50 };
        std::cout<<"low"<< temp.low()<<'\n';
        std::cout << "high" << temp.high() << '\n';
    }
    catch (std::invalid_argument & error){
        std::cout << error.what() << '\n';
    }
    try {
        TemperatureRange temp{ 50,100 };
        std::cout << "low" << temp.low() << '\n';
        std::cout << "high" << temp.high() << '\n';
    }
    catch (std::invalid_argument& error) {
        std::cout << error.what() << '\n';
    }
    
    return 0;
}
