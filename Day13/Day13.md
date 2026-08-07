# Day 13：从`struct`到`class`——让对象维护自己的规则

> 所属阶段：C++基础迁移（Week 2）  
> 正课必修：约125～145分钟  
> 巩固与选学：约20～40分钟  
> LeetCode：25分钟，单独计算  
> 前置：Day 5函数接口、Day 12强类型枚举

今天围绕一个问题展开：如果一组数据必须始终满足某些规则，怎样避免程序的任何位置都能随意破坏它？

## 学习目标

1. 理解`struct`与`class`的主要语言差异是默认访问权限；
2. 编写简单成员函数并通过对象调用；
3. 使用`private`隐藏需要维护的数据；
4. 使用公开成员函数检查修改请求；
5. 认识“对象始终保持合法”的类不变量。

## 内容边界

### 必修

- 成员变量、成员函数和对象；
- `public`与`private`；
- 只读成员函数末尾的`const`；
- 用返回值报告修改是否成功；
- 简单类不变量。

### 巩固

- `struct`适合简单公开数据，`class`适合需要维护规则的对象；
- getter不等于把所有成员都重新公开；
- 把验证逻辑放在最接近数据的位置。

### 选学

- 内存布局、空类大小和ABI；
- 友元、继承、多态；
- 构造函数的完整规则将在Day18系统学习。

今天先使用默认成员初始化建立合法起点，不提前展开构造函数体系。

## 一、`struct`和`class`都能有函数

```cpp
struct Point {
    int x{};
    int y{};

    void move(int dx, int dy)
    {
        x += dx;
        y += dy;
    }
};
```

对象调用成员函数：

```cpp
Point point{2, 3};
point.move(1, -1);
```

`struct`成员默认是`public`，`class`成员默认是`private`。除此之外，两者都可以拥有数据、函数和访问控制。不要把它们误解成“C结构体”和“真正的对象”两种完全不同的东西。

### 示例1：公开数据适合简单记录

```cpp
#include <iostream>

struct Measurement {
    int channel{};
    double value{};
};

void print(const Measurement& measurement)
{
    std::cout << "channel=" << measurement.channel
              << " value=" << measurement.value << '\n';
}

int main()
{
    Measurement sample{2, 3.3};
    print(sample);
}
```

如果数据只是被收集、传递和展示，没有复杂合法性规则，公开字段可以很清楚。

## 二、需要规则时使用封装

假设设备采样率只能在1到1000之间。公开字段无法阻止：

```cpp
config.sampleRate = -500;
```

把字段设为`private`，让修改经过成员函数：

```cpp
class DeviceConfig {
public:
    bool setSampleRate(int sampleRate)
    {
        if (sampleRate < 1 || sampleRate > 1000) {
            return false;
        }
        sampleRate_ = sampleRate;
        return true;
    }

    int sampleRate() const
    {
        return sampleRate_;
    }

private:
    int sampleRate_{100};
};
```

`sampleRate()`末尾的`const`表示这个成员函数不会修改对象的可观察状态，因此它也能在`const DeviceConfig`对象上调用。

### 示例2：修改失败时保持旧值

```cpp
#include <iostream>

int main()
{
    DeviceConfig config;
    std::cout << config.sampleRate() << '\n';

    std::cout << config.setSampleRate(500) << ' '
              << config.sampleRate() << '\n';

    std::cout << config.setSampleRate(-1) << ' '
              << config.sampleRate() << '\n';
}
```

预期最后一次输出的采样率仍为500。成员函数先验证，再写入，保证对象不会因为失败请求进入非法状态。

### 随堂练习1

给`DeviceConfig`增加`channel_`，合法范围为0到7。实现`setChannel`和`channel() const`，验证边界0、7、-1和8。

## 三、类不变量

类不变量是对象在公开操作完成后始终应满足的条件。例如：

- 采样率始终在1到1000之间；
- 通道始终在0到7之间；
- 名称不为空且长度不超过16。

不变量不是要求第一次学习类就完成大型领域建模。它只是提醒我们：如果多个函数都依赖一条规则，最好让对象自己守住这条规则。

### 示例3：只读查询

```cpp
class Counter {
public:
    void increment() { ++value_; }
    int value() const { return value_; }

private:
    int value_{};
};
```

修改操作和查询操作的意图很清楚。今天不要求把每个一行函数都拆到单独源文件，多文件组织在Day15学习。

### 随堂练习2

观察下面接口：

```cpp
int& sampleRate();
```

解释为什么返回私有字段的可写引用会绕过`setSampleRate`的检查。把它改成不会暴露写权限的查询接口。

## 四、什么时候继续使用`struct`

可以使用`struct`：

- 数据成员本来就是公开信息；
- 没有需要持续维护的不变量；
- 它主要用于把若干值组合传递。

可以优先使用`class`：

- 修改必须经过检查；
- 内部表示不希望被调用者依赖；
- 数据和行为共同表达一个概念。

这不是绝对风格法律。重点是访问权限与对象职责是否清楚。

## 重要错误提醒

1. 为所有字段机械生成getter和setter，不等于真正封装；
2. 查询成员函数漏写`const`会限制`const`对象使用；
3. 先修改字段再检查，会让失败路径短暂或永久留下非法状态；
4. 返回私有字段的非`const`引用可能完全绕过验证。

## 代码题一：受控计数器

实现`LimitedCounter`：

- 值初始为0；
- `increment()`只允许增加到10；
- `reset()`恢复为0；
- `value() const`返回当前值；
- 增加失败时返回`false`并保持10。

运行普通增加、到达上限和超过上限三个场景。

## 代码题二：设备配置类

实现`DeviceConfig`，私有保存：

- `std::string name_`，长度1～16；
- `int sampleRate_`，范围1～1000；
- `DeviceState state_`，初始为`offline`。

提供必要的修改与只读查询函数。非法名称或采样率必须返回`false`并保持原值。不要提供返回可写引用的getter。

在`main()`中验证合法修改、空名称、超长名称和采样率两个边界外值。

## 快速自测

1. `struct`和`class`最直接的默认访问差异是什么？
2. 成员函数末尾的`const`约束谁？
3. 为什么先验证再修改有助于保持不变量？
4. 简单测量结果一定要写成`class`吗？
5. 返回私有成员的可写引用有什么风险？

## 今日小结

1. `struct`和`class`都能定义数据与成员函数；
2. `private`帮助对象集中维护规则；
3. 只读成员函数应在参数列表后写`const`；
4. 修改失败时保持旧值，是容易理解且可靠的基本行为；
5. 封装服务于不变量，不是为了隐藏而隐藏。

## 算法副线

- 题目：392. Is Subsequence
- 难度：Easy
- 官方链接：[LeetCode 392](https://leetcode.com/problems/is-subsequence/)
- 建议时间：25分钟
- 训练目标：用双指针按顺序匹配两个字符串
- 三级提示：[algorithms/day-013.md](../algorithms/day-013.md)

下一课将把本周的生命周期、安全访问、固定数组、字符串、枚举和封装组合成命令行设备配置器v2。
