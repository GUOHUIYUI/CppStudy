#include <iostream>
#include <stdexcept>

class Trace {
public:
    explicit Trace(std::string name)
        :name_{ name }
    {
        std::cout << "Construct" << name_ << '\n';
    }
    ~Trace()
    {
        std::cout << "destory" << name_ << '\n';
    }

private:
    std::string name_;
};

/*
    Construct outer
    Construct inner
    Construct inner2
    destory inner2
    destory inner
    destory outer
*/
int main()
{
    Trace outer1{ "outer" };
    {
        Trace inner1{ "inner" };
        {
            Trace inner2{ "inner2" };   
        }
    }
    return 0;
}
