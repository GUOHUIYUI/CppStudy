# Day 15：把程序拆成头文件与源文件

> 所属阶段：C++基础迁移（Week 3）  
> 正课必修：约125～145分钟  
> 巩固与选学：约20～35分钟  
> LeetCode：30分钟，单独计算  
> 前置：Day 1编译链、Day 5函数接口、Day 13类、Day 14配置器

Day14的配置器已经把字符串、枚举、数组和类组合在一个`main.cpp`里。代码继续增长时，所有内容挤在一个文件中会越来越难查找，也会让不同模块彼此干扰。

今天解决一个核心问题：怎样把声明放进头文件、实现放进源文件，让多个源文件能够正确编译并在最后链接成一个程序？

## 学习目标

完成必修后，你应该能够：

1. 区分声明和定义，并说明编译器与链接器分别需要什么；
2. 把函数或简单类拆分为`.h`、`.cpp`和`main.cpp`；
3. 使用include guard防止同一头文件在一个翻译单元中被重复展开；
4. 识别“未定义符号”和“重复定义”两类典型链接错误；
5. 用自己的话解释ODR在当前阶段最实用的规则。

## 今天的内容边界

### 必修

- 声明与定义；
- 头文件、源文件和翻译单元；
- `#include`实际做了什么；
- include guard；
- 函数与简单类的多文件拆分；
- 常见编译错误和链接错误。

### 巩固

- 头文件只包含接口所需内容；
- `.cpp`优先包含自己的头文件；
- 头文件中的普通函数定义为何容易违反ODR；
- `inline`与`constexpr`在头文件中的基本位置。

### 选学

- 预编译头、Unity Build、C++20 Modules；
- 完整ODR措辞、链接器符号格式和ABI；
- 静态库、动态库和CMake将在后续课程系统学习。

今天暂时使用全局名称。命名空间、匿名命名空间和内部链接安排在Day16，不提前混入主线。

## 一、从一次构建过程看多文件程序

假设工程包含：

```text
main.cpp
temperature.cpp
temperature.h
```

构建时可以先把过程理解为：

```text
main.cpp --------> main.obj --------\
                                   +--> linker --> app.exe
temperature.cpp -> temperature.obj -/
```

每个`.cpp`单独经过预处理和编译，产生一个目标文件；链接器再把多个目标文件中的定义连接起来。

头文件不会独立编译成目标文件。`#include "temperature.h"`可以先理解为：预处理器把头文件文本展开到当前`.cpp`中。

一个`.cpp`连同它展开的头文件，称为一个翻译单元。今天只需会用这个概念解释错误，不要求背标准定义。

## 二、声明告诉编译器“它存在”

函数声明：

```cpp
double celsiusToFahrenheit(double celsius);
```

它告诉编译器函数的名称、参数和返回类型，但没有提供函数体。

函数定义：

```cpp
double celsiusToFahrenheit(double celsius)
{
    return celsius * 9.0 / 5.0 + 32.0;
}
```

定义真正提供实现。调用处编译时只需要先看到声明；最终链接时必须找到匹配的定义。

### 示例1：拆分一个转换函数

`temperature.h`：

```cpp
#ifndef TEMPERATURE_H
#define TEMPERATURE_H

double celsiusToFahrenheit(double celsius);

#endif
```

`temperature.cpp`：

```cpp
#include "temperature.h"

double celsiusToFahrenheit(double celsius)
{
    return celsius * 9.0 / 5.0 + 32.0;
}
```

`main.cpp`：

```cpp
#include "temperature.h"

#include <iostream>

int main()
{
    std::cout << celsiusToFahrenheit(25.0) << '\n';
    return 0;
}
```

三个文件共同组成一个程序。`main.cpp`不需要知道转换公式，只需要知道函数接口。

### 随堂练习1

在同一组文件中增加：

```cpp
double fahrenheitToCelsius(double fahrenheit);
```

先只写声明并调用，观察链接错误；再补上完全匹配的定义并重新构建。记录两次构建阶段有什么不同。

## 三、include guard防止重复展开

一个头文件可能通过多条包含路径进入同一个`.cpp`：

```text
main.cpp -> device.h -> status.h
main.cpp ------------> status.h
```

include guard确保头文件内容在单个翻译单元中只展开一次：

```cpp
#ifndef DEVICE_STATUS_H
#define DEVICE_STATUS_H

enum class DeviceState {
    offline,
    idle,
    running
};

#endif
```

宏名应在项目中足够独特，并与文件用途对应。

许多编译器也支持：

```cpp
#pragma once
```

它简单常用，但不是C++标准本身规定的指令。本课程练习优先手写include guard，先看清它解决的问题。

include guard只解决“同一个翻译单元内重复包含”，不能让头文件里的普通函数定义自动满足整个程序的ODR。

## 四、ODR的当前实用版本

ODR是One Definition Rule，单一定义规则。现阶段先掌握两条：

1. 普通非`inline`函数在整个程序中只能有一个定义；
2. 类定义可以出现在多个翻译单元，但每处必须来自相同的头文件并保持一致。

### 错误示例：在头文件定义普通函数

`math_ops.h`：

```cpp
int add(int left, int right)
{
    return left + right;
}
```

如果`main.cpp`和`report.cpp`都包含它，就会各自产生一个`add`定义，链接时通常报告重复定义。

最直接的基础修正是：

- 头文件只保留声明；
- 一个`.cpp`提供定义。

```cpp
// math_ops.h
int add(int left, int right);
```

```cpp
// math_ops.cpp
#include "math_ops.h"

int add(int left, int right)
{
    return left + right;
}
```

Day5见过的`inline`允许同一个完全相同的定义出现在多个翻译单元，因此短小函数可以定义在头文件中。今天不要为了省一个`.cpp`就给所有函数加`inline`；先学会正常拆分。

`constexpr`函数隐式具有`inline`属性，通常需要把定义放在头文件中，让调用处看到定义。高级规则以后再展开。

## 五、把类拆到多个文件

类定义通常放在头文件中，成员函数实现可以放在`.cpp`中。

`counter.h`：

```cpp
#ifndef COUNTER_H
#define COUNTER_H

class Counter {
public:
    bool increment();
    int value() const;

private:
    int value_{};
};

#endif
```

`counter.cpp`：

```cpp
#include "counter.h"

bool Counter::increment()
{
    if (value_ >= 10) {
        return false;
    }
    ++value_;
    return true;
}

int Counter::value() const
{
    return value_;
}
```

类外定义成员函数时，`Counter::`说明这个函数属于`Counter`。声明和定义必须在返回类型、参数以及成员函数末尾的`const`等方面一致。

### 示例2：为什么`.cpp`先包含自己的头文件

推荐在实现文件开头写：

```cpp
#include "counter.h"

#include <iostream>
```

自己的头文件放在最前面，有助于暴露“头文件遗漏必要包含”或“声明与定义不一致”等问题。不要依赖其他头文件碰巧先提供某个类型。

### 随堂练习2

把Day13的`LimitedCounter`拆成`limited_counter.h`、`limited_counter.cpp`和`main.cpp`。故意把定义写成：

```cpp
int LimitedCounter::value()
```

观察它与头文件中的`int value() const;`为何不匹配，然后恢复正确的`const`。

## 六、判断错误发生在哪一阶段

### 1. 编译错误：调用前没有可见声明

```text
identifier not found
was not declared in this scope
```

检查是否包含正确头文件、名称是否拼错、声明是否可见。

### 2. 链接错误：有声明，但找不到定义

```text
unresolved external symbol
undefined reference
```

检查是否遗漏`.cpp`、定义签名是否与声明一致、项目是否真的编译了该源文件。

### 3. 链接错误：同一普通函数定义多次

```text
already defined
multiple definition
```

检查是否把普通函数定义写进了被多个`.cpp`包含的头文件，或同一个`.cpp`被错误加入两次。

## 重要错误提醒

1. include guard不能修复跨多个翻译单元的普通函数重复定义；
2. 声明与定义的参数、返回类型和成员函数`const`必须匹配；
3. 只把声明写进头文件却忘记把实现`.cpp`加入项目，会在链接阶段失败；
4. 公共头文件中不要写`using namespace std;`，它会影响所有包含者。

## 代码题一：多文件单位转换器

在`01_多文件函数拆分`中创建并完成：

```text
temperature.h
temperature.cpp
main.cpp
```

提供摄氏度与华氏度双向转换。要求：

- 头文件使用include guard，只放声明；
- 两个函数定义放在`temperature.cpp`；
- `main.cpp`只通过头文件使用接口；
- 至少验证0°C、100°C和32°F；
- 在Visual Studio中确认三个文件都属于同一项目。

## 代码题二：修复ODR与链接错误

在`02_ODR与链接错误实验`中依次制造并修复三种错误：

1. 调用函数但没有可见声明；
2. 有声明但没有把实现源文件加入项目；
3. 把普通函数定义写在头文件中，并从两个`.cpp`包含它。

每次保存一条关键错误信息，并写一句根因。最终版本必须恢复为可编译结构：头文件声明、单个源文件定义、其他源文件只通过头文件调用。

## 综合改造：拆分Day14配置器

完成前两题后，把Day14中的`DeviceConfig`拆为：

```text
device_config.h
device_config.cpp
main.cpp
```

今天只拆`DeviceConfig`；命令解析和采样统计可以暂时留在`main.cpp`。不要顺便引入命名空间，Day16会在这个结构上继续改造。

## 快速自测

1. 声明和定义分别提供什么信息？
2. 头文件是否会单独生成目标文件？
3. include guard解决的是哪个范围内的重复包含？
4. “有声明、无定义”通常发生在编译阶段还是链接阶段？
5. 为什么不应在公共头文件中定义普通非`inline`函数？

## 今日小结

1. 每个`.cpp`分别编译，链接器再组合目标文件；
2. 头文件主要暴露声明，源文件提供普通函数定义；
3. include guard防止同一翻译单元重复展开头文件；
4. ODR要求普通非`inline`函数在程序中只有一个定义；
5. 能区分编译错误和链接错误，是调试多文件工程的第一步。

## 算法副线

- 题目：350. Intersection of Two Arrays II
- 难度：Easy
- 官方链接：[LeetCode 350](https://leetcode.com/problems/intersection-of-two-arrays-ii/)
- 建议时间：30分钟
- 训练目标：选择计数或排序双指针处理带重复元素的交集
- 三级提示：[algorithms/day-015.md](../algorithms/day-015.md)

下一课将在今天的多文件结构上加入命名空间、匿名命名空间和内部链接，避免不同模块之间的名称冲突。
