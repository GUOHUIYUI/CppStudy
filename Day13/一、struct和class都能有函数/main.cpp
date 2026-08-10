#include <iostream>


//struct成员默认是public，class成员默认是private。除此之外，两者都可以拥有数据、函数和访问控制
struct Point {
    int x{};
    int y{};
    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }
};

//示例1：公开成员适合简单记录
//如果数据只是被收集、传递和展示，没有复杂合法性规则，公开字段可以很清楚
struct Measurement {
    int channel{};
    double value{};
};

void print(const Measurement &measurement)
{
    std::cout << "channle:  " << measurement.channel
        << " value:   " << measurement.value << "\n";
}

int main()
{
    std::cout << "Hello, world!\n";
    Point point{ 1,2 };
    point.move(2, 3);
    Measurement sample(2, 2.1);
    print(sample);

    return 0;
}