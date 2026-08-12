# Day 16：用命名空间组织多文件代码

> 所属阶段：C++基础迁移（Week 3）
> 正课必修：约100～120分钟
> 巩固与选学：约20～35分钟
> LeetCode：30分钟，单独计算
> 前置：Day 15头文件、源文件、翻译单元与链接

Day15解决了“代码放在哪个文件”的问题。文件变多以后，还会出现另一个问题：两个模块可能都定义`Config`、`State`或`parse`，这些名字在全局作用域中容易冲突，也不容易看出属于哪个模块。

今天解决一个核心问题：怎样用命名空间表达代码归属，同时把只供单个`.cpp`使用的辅助实现藏在该翻译单元内部？

## 学习目标

完成必修后，你应该能够：

1. 定义并使用普通命名空间和嵌套命名空间；
2. 在头文件与源文件中保持同一个命名空间结构；
3. 区分限定名、using声明和using指令；
4. 使用匿名命名空间隐藏`.cpp`内部辅助函数；
5. 避免在公共头文件中使用`using namespace`污染包含者。

## 今天的内容边界

### 必修

- 命名空间定义和`::`限定；
- C++17嵌套命名空间语法；
- 多文件项目中的命名空间一致性；
- using声明与using指令的基本区别；
- 匿名命名空间和内部链接。

### 巩固

- 命名空间别名；
- 在较小作用域内使用using声明；
- 把实现细节留在`.cpp`而不是公共头文件。

### 选学

- `inline namespace`与库版本管理；
- ADL、模块和大型库的命名规范；
- 链接器如何编码命名空间名称。

今天不展开命名空间与模板、运算符重载的交互，也不建立复杂目录规范。

## 一、命名空间给名字增加上下文

两个模块都可以有自己的`Config`：

```cpp
namespace audio {
struct Config {
    int volume{};
};
}

namespace network {
struct Config {
    int timeoutMs{};
};
}
```

使用时写限定名：

```cpp
audio::Config audioConfig{80};
network::Config networkConfig{1000};
```

`::`是作用域解析运算符。`audio::Config`明确表示“命名空间`audio`里的`Config`”，而不是把所有名字重新变得独一无二。

### 示例1：同名函数属于不同模块

```cpp
#include <iostream>

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

int main()
{
    std::cout << metric::convert(1.5) << '\n';
    std::cout << display::convert(1.5) << '\n';
}
```

这两个`convert`不会冲突，因为它们的完整名称不同。

### 随堂练习1

建立`temperature`和`distance`两个命名空间，各自定义一个`toBaseUnit(double)`函数。调用时保留完整限定名，并解释为什么函数名相同仍能共存。

## 二、嵌套命名空间表达模块层次

Day14配置器可以使用：

```cpp
namespace device::config {
class DeviceConfig {
    // ...
};
}
```

这是C++17的嵌套命名空间语法，等价于：

```cpp
namespace device {
namespace config {
// ...
}
}
```

使用时写：

```cpp
device::config::DeviceConfig config;
```

层次应服务于真实模块关系。基础项目中`device::config`已经足够，不需要堆叠五六层名称来显得工程化。

## 三、多文件中的命名空间必须一致

`device_config.h`：

```cpp
#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#include <string>
#include <string_view>

namespace device::config {

class DeviceConfig {
public:
    bool setName(std::string_view name);
    const std::string& name() const;

private:
    std::string name_{"device"};
};

} // namespace device::config

#endif
```

`device_config.cpp`：

```cpp
#include "device_config.h"

namespace device::config {

bool DeviceConfig::setName(std::string_view name)
{
    if (name.empty() || name.size() > 16) {
        return false;
    }
    name_ = name;
    return true;
}

const std::string& DeviceConfig::name() const
{
    return name_;
}

} // namespace device::config
```

声明和定义必须属于同一个命名空间。如果头文件声明`device::config::DeviceConfig`，源文件却在全局命名空间实现另一个同名类或函数，原声明仍然没有定义。

### 示例2：命名空间跨文件延续

同一个命名空间可以在多个文件和多个位置重复打开：

```cpp
namespace device::config {
bool isValidRate(int rate);
}
```

```cpp
namespace device::config {
bool isValidRate(int rate)
{
    return rate >= 1 && rate <= 1000;
}
}
```

这不是定义两个命名空间，而是在不同位置向同一个命名空间添加成员。

### 随堂练习2

把Day15的单位转换器放进`units::temperature`命名空间。头文件、源文件和调用处都要修改。故意只修改头文件，观察链接器为何找不到原声明对应的定义，再完成全部修改。

## 四、限定名、using声明和using指令

### 完整限定名

```cpp
device::config::DeviceConfig config;
```

它最清楚，尤其适合公共接口和名称可能冲突的位置。

### using声明：引入一个名字

```cpp
using device::config::DeviceConfig;

DeviceConfig config;
```

它只引入指定名字。可以在较短的函数作用域中使用，减少重复书写。

### using指令：让整个命名空间参与查找

```cpp
using namespace device::config;
```

它会让命名空间中的许多名字都参与后续查找，名称来源更难观察，也更容易与未来新增名字冲突。

公共头文件中禁止写：

```cpp
using namespace std;
```

因为每个包含该头文件的源文件都会受到影响。`.cpp`内部的小作用域即使技术上可用，也应先考虑完整限定名或using声明。

### 命名空间别名

名字确实较长时，可以在局部建立别名：

```cpp
namespace cfg = device::config;

cfg::DeviceConfig config;
```

别名没有创建新命名空间，只是给已有命名空间提供短名称。

## 五、匿名命名空间隐藏实现细节

某些辅助函数只应在当前`.cpp`中使用：

```cpp
// device_config.cpp
#include "device_config.h"

namespace {

bool isValidName(std::string_view name)
{
    return !name.empty() && name.size() <= 16;
}

} // namespace
```

匿名命名空间中的名字具有内部链接：其他翻译单元不能通过声明连接到这个`isValidName`。另一个`.cpp`可以拥有自己的同名辅助函数，两者不会发生链接冲突。

随后公开成员函数在同一个`.cpp`中使用它：

```cpp
namespace device::config {

bool DeviceConfig::setName(std::string_view name)
{
    if (!isValidName(name)) {
        return false;
    }
    name_ = name;
    return true;
}

}
```

这里有两种不同职责：

- `device::config`表示公开代码属于哪个模块；
- 匿名命名空间表示辅助名字只属于当前翻译单元。

不要把需要跨文件使用的函数放进匿名命名空间，否则其他源文件无法链接它。也不要把匿名命名空间写进公共头文件；每个包含者会得到各自独立的名字，通常不是接口想表达的含义。

## 六、内部链接与`static`的关系

在命名空间作用域，旧式C/C++代码也常写：

```cpp
static bool isValidName(std::string_view name);
```

这里的`static`同样赋予函数内部链接。现代C++中，多个相关辅助类型、常量和函数通常统一放进匿名命名空间，更容易看出它们共同属于`.cpp`内部实现。

今天只要求认识这两种写法，不需要批量重构所有旧C代码。

## 重要错误提醒

1. 头文件声明与源文件定义必须位于相同命名空间；
2. 公共头文件中的`using namespace`会污染所有包含者；
3. 匿名命名空间只适合当前`.cpp`的实现细节，不能承载跨文件接口；
4. 命名空间解决名称归属，不替代`private`的数据封装。

## 代码题一：为单位转换器增加命名空间

在`01_命名空间与多文件`中完成多文件程序：

```text
temperature.h
temperature.cpp
main.cpp
```

要求：

- 两个转换函数属于`units::temperature`；
- 头文件不使用任何`using namespace`；
- 源文件定义与头文件声明处于相同命名空间；
- `main()`先用完整限定名调用，再用局部命名空间别名调用；
- 验证0°C、100°C和32°F。

## 代码题二：配置模块与内部辅助函数

在`02_配置模块与内部链接`中建立：

```text
device_config.h
device_config.cpp
main.cpp
```

要求：

- `DeviceConfig`属于`device::config`；
- 名称长度为1～16，采样率为1～1000；
- `isValidName`与`isValidRate`只在`device_config.cpp`内部使用，放入匿名命名空间；
- `main.cpp`只通过公共类接口修改和查询配置；
- 非法修改保持原值。

测试合法值以及名称空串、17字符名称、采样率0和1001。

## 综合改造：Day14配置器的名称结构

如果Day15尚未完成配置器拆分，可以直接在本题结构中完成。建议归属：

```text
device::config::DeviceConfig
device::config::DeviceState
device::command::CommandResult
device::command::processCommand(...)
```

先让类和函数归属清楚即可。命令错误信息的进一步设计留到Day17，不在今天引入异常或复杂结果类型。

## 快速自测

1. `device::config::DeviceConfig`中的两个`::`表达什么？
2. 同一个命名空间能否在多个文件中重复打开？
3. using声明和using指令的影响范围有什么区别？
4. 为什么公共头文件不应写`using namespace std;`？
5. 匿名命名空间中的辅助函数能否供另一个`.cpp`调用？

## 今日小结

1. 命名空间让名字表达模块归属并避免全局冲突；
2. 多文件声明和定义必须保持相同命名空间；
3. using声明只引入指定名字，using指令会扩大名称查找范围；
4. 匿名命名空间适合隐藏单个`.cpp`的辅助实现；
5. 公共头文件应避免任何会污染包含者的using指令。

## 算法副线

- 题目：169. Majority Element
- 难度：Easy
- 官方链接：[LeetCode 169](https://leetcode.com/problems/majority-element/)
- 建议时间：30分钟
- 训练目标：比较计数、排序与Boyer–Moore投票思路
- 三级提示：[algorithms/day-016.md](../algorithms/day-016.md)

下一课将学习显式返回状态、错误码与异常概览，让解析失败不再只剩一个含义模糊的`false`。
