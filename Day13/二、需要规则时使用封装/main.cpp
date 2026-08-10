#include <iostream>


//公开字段无法阻止非法值修改
class DeviceConfig {
public:
    bool setSampleRate(int sampleRate)
    {
        if (sampleRate < 1 || sampleRate>1000)
        {
            return false;
        }
        sampleRate_ = sampleRate;
        return true;
        
    }
    int sampleRate() const  //末尾的const表示这个成员函数不会修改对象的可观察状态，因此它也能在const DeviceConfig对象中调用
    {
        return sampleRate_;
    }
    ///int& sampleRate();解释为什么返回私有字段的可写引用会绕过`setSampleRate`的检查。   因为这个直接返回了内部对象的引用，而通过引用可以修改对象本身的值  增加const则可以避免通过引用修改对象本身
    const int &sampleRate()
    {
        return sampleRate_;
    }//
    bool setChannel(int channel)
    {
        if (channel < 0 || channel>7)
        {
            return false;
        }
        channel_ = channel;
        return true;

    }
    int channel() const  //末尾的const表示这个成员函数不会修改对象的可观察状态，因此它也能在const DeviceConfig对象中调用
    {
        return channel_;
    }
private:
    int sampleRate_{100};
    int channel_{ 1 };
};
int main()
{
    std::cout << "Hello, world!\n";
    DeviceConfig config;
    std::cout << config.sampleRate() << '\n';

    std::cout << config.setSampleRate(500) << ' '
        << config.sampleRate() << '\n';

    std::cout << config.setSampleRate(-1) << ' '
        << config.sampleRate() << '\n';

    std::cout << config.channel() << '\n';

    std::cout << config.setChannel(0) << ' '
        << config.channel() << '\n';

    std::cout << config.setChannel(7) << ' '
        << config.channel() << '\n';
    std::cout << config.setChannel(-1) << ' '
        << config.channel() << '\n';

    std::cout << config.setChannel(8) << ' '
        << config.channel() << '\n';

 

    return 0;
}