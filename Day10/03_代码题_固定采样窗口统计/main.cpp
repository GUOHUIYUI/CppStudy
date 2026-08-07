#include <array>
#include <cstddef>
#include <iostream>



/*
- 使用`std::array`和范围`for`；
- 平均值使用`double`计算，避免整数除法；
- 不使用`std::vector`；
- 不调用尚未学习的标准算法；
- 在`main()`中至少运行一组普通数据，并自行增加一组边界数据。
*/

void samplePrint(const std::array<int, 8>& samples)
{
    int count{}, sum{}, max{samples[0]}, min{samples[0]};
    double avg{};
    for (int value : samples)
    {
        count++;
        sum += value;
        if (value > max)
        {
            max = value;
        }
        if (value < min)
        {
            min = value;
        }

    }
    avg=static_cast<double>(sum)/count;
    std::cout<<"count:  "<<count<<"  sum:  "<<sum<<"  avg:  "<<avg<<"  max:  "<<max<<"  min:  "<<min<<std::endl;

}


/*
    * std::array<int, 5>`中的`5`表示什么？  表示数组总共有多少个元素
    * 一个包含5个元素的数组，最后一个合法下标是多少？  4
    * `operator[]`和`at()`在边界检查方面有什么区别？  operator[]不对边界进行检查 at()检查出越界会抛异常
    * 为什么`for (int value : values)`不能修改数组元素？    因为value是values数组元素的副本
    * 原生数组传入普通函数后，为什么经常还要传递长度？        原生数组传入普通函数后，数组会退化为指针，所以需要长度
    
*/
int main()
{
    std::array<int, 8> samples{ 2,3,64,7,8,2,8,5 };
    //第一个元素           最后一个元素        指定下标的元素         元素数量
    std::cout << samples.front() << "   " << samples.back() << "    " <<samples.at(4)<<"      " << samples.size() << std::endl;
    samplePrint(samples);
    return 0;
}
