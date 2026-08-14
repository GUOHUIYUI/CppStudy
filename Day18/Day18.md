# Day 18：让对象从创建时就处于合法状态

> 所属阶段：C++基础迁移（Week 3）
> 正课必修：约130～150分钟
> 巩固与选学：约20～35分钟
> LeetCode：25分钟，单独计算
> 前置：Day 13类与封装、Day 17错误结果、Day 8对象生命周期

以前的类通常先默认创建，再调用若干`set`函数补齐数据。这会留下一个问题：对象刚创建、尚未设置完成的那段时间，它是否有效？

今天解决一个核心问题：怎样使用构造函数和成员初始化列表，让对象从诞生时就满足最基本的不变量，并认识析构函数在对象结束生命周期时承担的职责？

## 学习目标

1. 写出默认构造函数和带参数构造函数；
2. 使用成员初始化列表初始化数据成员；
3. 解释初始化列表与构造函数体内赋值的区别；
4. 在构造阶段检查类不变量并拒绝非法参数；
5. 说明析构函数何时调用，以及今天为什么通常不需要手写它。

## 内容边界

### 必修

- 构造函数的名称、调用时机和基本重载；
- 成员初始化列表；
- 默认成员初始化与构造参数的配合；
- 构造时建立类不变量；
- 析构函数的语法与自动调用时机。

### 巩固

- `const`成员和引用成员必须在初始化列表中初始化；
- 成员按声明顺序初始化，而不是按列表书写顺序；
- 默认析构函数已足够处理普通成员。

### 选学

- 委托构造、转换构造与`explicit`；
- 构造函数异常的完整安全规则；
- RAII和资源释放将在Day29以后系统学习。

今天不讲拷贝构造、移动构造、智能指针和继承。

## 一、构造函数负责建立对象

构造函数与类同名，没有返回类型：

```cpp
class Counter {
public:
    Counter()
        : value_{0}
    {
    }

    explicit Counter(int start)
        : value_{start}
    {
    }

private:
    int value_{};
};
```

创建对象时会自动选择匹配的构造函数：

```cpp
Counter first;       // 默认构造
Counter second{10};  // 带参数构造
```

这里先把`explicit`理解为：要求调用者明确写出`Counter{10}`，不允许整数悄悄变成`Counter`。它会在Day23进一步学习。

### 示例1：观察构造和析构顺序（建议手敲）

```cpp
#include <iostream>
#include <string>

class Trace {
public:
    explicit Trace(std::string name)
        : name_{name}
    {
        std::cout << "construct " << name_ << '\n';
    }

    ~Trace()
    {
        std::cout << "destroy " << name_ << '\n';
    }

private:
    std::string name_;
};

int main()
{
    Trace outer{"outer"};
    {
        Trace inner{"inner"};
    }
    std::cout << "inner scope ended\n";
}
```

先预测输出，再运行。`inner`离开内部作用域时析构，`outer`在`main`结束时析构。析构函数没有参数和返回类型，一个类只能有一个析构函数。

这个示例用打印帮助观察生命周期。正常业务类不应为了“证明存在析构函数”而随意打印。

### 随堂练习1

增加第三个对象并放入另一个嵌套作用域。运行前写下构造和析构顺序，再核对输出。

## 二、初始化列表是真正的成员初始化

下面两段代码看起来接近，但过程不同：

```cpp
class Label {
public:
    explicit Label(std::string text)
        : text_{text}
    {
    }

private:
    std::string text_;
};
```

与：

```cpp
class Label {
public:
    explicit Label(std::string text)
    {
        text_ = text;
    }

private:
    std::string text_;
};
```

第一种直接使用`text`构造成员；第二种先默认构造`text_`，进入函数体后再赋值。对于`int`差异可能不明显，但对`std::string`等类对象，初始化列表更准确地表达意图。

某些成员只能在初始化列表中初始化：

```cpp
class Reading {
public:
    Reading(int id, double value)
        : id_{id}, value_{value}
    {
    }

private:
    const int id_;
    double value_{};
};
```

`const`成员创建后不能再赋值，因此不能等到构造函数体中处理。

## 三、成员初始化顺序看声明

```cpp
class Range {
public:
    Range(int low, int high)
        : high_{high}, low_{low}
    {
    }

private:
    int low_;
    int high_;
};
```

虽然初始化列表先写`high_`，真正的顺序仍是成员在类中的声明顺序：先`low_`，后`high_`。建议初始化列表也按声明顺序书写，避免误读和编译器警告。

如果一个成员的初始值依赖另一个成员，忽略声明顺序可能读到尚未初始化的数据。这类错误不要靠调整初始化列表文字顺序修补，而要调整成员声明或直接使用构造参数。

## 四、构造时建立不变量

假设配置对象必须满足：名称非空且不超过16字符，采样率为1～1000。构造函数不能像普通解析函数一样返回`ParseResult`，因此需要先决定非法参数的语义。

当前阶段采用一个简单方案：

- 用户文本先由Day17的解析函数检查；
- 构造函数仍检查最终参数，防止其他调用者绕过解析；
- 违反构造要求时抛出`std::invalid_argument`；
- 普通命令输入错误仍使用显式结果，不改成异常。

### 示例2：合法的配置对象（建议手敲）

```cpp
#include <stdexcept>
#include <string>
#include <utility>

class DeviceConfig {
public:
    DeviceConfig(std::string name, int rate)
        : name_{std::move(name)}, rate_{rate}
    {
        if (name_.empty() || name_.size() > 16) {
            throw std::invalid_argument{"invalid device name"};
        }
        if (rate_ < 1 || rate_ > 1000) {
            throw std::invalid_argument{"rate must be 1 to 1000"};
        }
    }

    const std::string& name() const { return name_; }
    int rate() const { return rate_; }

private:
    std::string name_;
    int rate_;
};
```

`std::move`今天只理解为：允许把按值接收的字符串内容转入成员，避免一次不必要复制。移动语义会在Day32正式学习；不熟悉时写`name_{name}`也完全可以。

构造函数抛出时，对象不会完成创建。调用处若要继续运行，需要在合适层捕获：

```cpp
try {
    DeviceConfig config{"sensor-a", 100};
    std::cout << config.name() << '\n';
} catch (const std::invalid_argument& error) {
    std::cout << error.what() << '\n';
}
```

### 随堂练习2

分别尝试空名称、17字符名称、采样率0、采样率1001和合法边界值。确认非法对象没有进入后续使用分支。

## 五、什么时候需要自己写析构函数

只包含`int`、`std::string`、`std::array`等普通成员时，编译器生成的析构函数已经会逐个销毁成员：

```cpp
class DeviceConfig {
    // 不需要为了清理string而手写析构函数
};
```

你也可以显式写：

```cpp
~DeviceConfig() = default;
```

但这通常没有增加信息。等类真正拥有文件、句柄或动态内存等资源时，析构函数才会承担释放职责；Day29～35会集中学习。

## 重要错误提醒

1. 构造函数没有返回类型，连`void`也不能写；
2. 成员按声明顺序初始化，不按初始化列表顺序；
3. 不要先创建明显非法对象，再期待调用者记得补齐全部字段；
4. 不要为普通成员编写空的或重复清理的析构函数。

## 代码题一：带不变量的温度区间

在`01_构造与初始化列表`中实现`TemperatureRange`：

- 构造时接收下限与上限；
- 下限不能大于上限，否则拒绝构造；
- 两个只读成员函数返回上下限；
- 使用初始化列表；
- 测试相等边界、正常区间和反向区间。

先独立完成；不要求添加动态内存或自定义析构函数。

## 代码题二：合法配置对象

在`02_合法配置对象`中把类拆成`.h/.cpp/main.cpp`：

- 构造函数接收名称、采样率和设备状态；
- 名称长度1～16，采样率1～1000；
- 非法构造参数不能产生可继续使用的对象；
- 合法对象创建后可以读取三个字段；
- `main()`至少覆盖四个非法输入和两个合法边界。

命令文本的格式错误继续使用Day17的显式结果；本题只关注对象最终构造参数。

## 快速自测

1. 构造函数为什么没有返回类型？
2. 初始化列表与构造函数体内赋值有什么区别？
3. 初始化列表的书写顺序能否改变成员实际初始化顺序？
4. 只有`std::string`和整数成员的类是否必须手写析构函数？
5. 用户输入错误为什么不必全部改用异常？

## 今日小结

1. 构造函数负责让对象从创建时就满足基本条件；
2. 成员初始化列表直接初始化成员，是构造函数的常规写法；
3. 成员始终按声明顺序初始化；
4. 析构函数在生命周期结束时自动调用，普通成员通常不需要手写清理；
5. 类不变量应在所有创建路径上成立。

## 算法副线

- 题目：136. Single Number
- 难度：Easy
- 官方链接：[LeetCode 136](https://leetcode.com/problems/single-number/)
- 建议时间：25分钟
- 训练目标：利用异或的交换律、结合律和成对抵消性质
- 三级提示：[algorithms/day-018.md](../algorithms/day-018.md)

下一课不引入新语法，而是集中调试编译、链接、生命周期和接口歧义问题。
