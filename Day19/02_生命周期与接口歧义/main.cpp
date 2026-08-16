#include <iostream>
#include <string>


const std::string makeLabel()
{
    std::string label{ "ready" };
    return label; // 故意错误
}

class Sample {
public:
    explicit Sample(int value)
        : scaled_{ raw_ * 2 }, raw_{ value }
    {
    }

private:
    int raw_;
    int scaled_;
   
};

class DeviceConfig {
public:
    DeviceConfig(const std::string name, int rate)
        :name_(name), rate_(rate)
    {

    }
    void setNmae(const std::string name)
    {
        name_ = name;
    }
    void setRate(int rate)
    {
        rate_ = rate;
    }
    private:
    std::string name_;
    int rate_;
};
void report(int value);
void report(int value, int precision = 2);

void connect(int channel);
void connect(const char* address);
int main()
{
    connect(0);
    connect(nullptr);
    return 0;
}
