# Day 12：用`enum class`表达有限状态

> 所属阶段：C++基础迁移（Week 2）  
> 正课必修：约100～120分钟  
> 巩固与选学：约20～30分钟  
> LeetCode：30分钟，单独计算  
> 前置：C枚举和宏、Day 5函数接口

今天解决的问题是：当一个值只能取少量合法状态时，怎样让编译器帮助阻止无关整数和不同类别互相混用？

## 学习目标

1. 声明并使用`enum class`；
2. 理解强类型枚举不会自动变成整数；
3. 按需要指定底层类型；
4. 区分单选状态、错误码和位标志三种用途；
5. 用强类型状态替换宏常量。

## 内容边界

### 必修

- `enum class`的定义、作用域和比较；
- `switch`处理有限状态；
- 显式转换与底层类型；
- 状态值和错误码的基本设计。

### 巩固

- 给枚举指定`std::uint8_t`或`std::uint16_t`；
- 为日志编写`toString`函数；
- 识别不完整的`switch`。

### 选学

- 位标志的按位组合；
- 自定义位运算符、反射和序列化框架。

今天不要求实现通用位标志库，也不把枚举当成任意整数容器。

## 一、为什么不用一组宏

```cpp
#define DEVICE_IDLE 0
#define DEVICE_RUNNING 1
#define ERROR_TIMEOUT 1
```

`DEVICE_RUNNING`和`ERROR_TIMEOUT`实际上都只是整数1，编译器无法阻止它们混用。`enum class`把类别也放进类型中：

```cpp
enum class DeviceState {
    idle,
    running,
    fault
};

enum class ErrorCode {
    none,
    timeout,
    invalidCommand
};
```

访问枚举值时必须写作用域：

```cpp
DeviceState state{DeviceState::idle};
```

不能直接把`ErrorCode::timeout`赋给`DeviceState`。

### 示例1：状态转换与显示

```cpp
#include <iostream>
#include <string_view>

enum class DeviceState { idle, running, fault };

std::string_view toString(DeviceState state)
{
    switch (state) {
    case DeviceState::idle: return "idle";
    case DeviceState::running: return "running";
    case DeviceState::fault: return "fault";
    }
    return "unknown";
}

int main()
{
    DeviceState state{DeviceState::idle};
    state = DeviceState::running;
    std::cout << toString(state) << '\n';
}
```

末尾的`return "unknown"`用于让函数在未来出现意外值时仍有明确返回路径。不要把它理解成可以随意制造非法枚举值。

### 随堂练习1

增加`stopping`状态，并同步修改`toString`。然后故意漏掉一个`case`，观察编译器在当前警告配置下是否提醒你。

## 二、底层类型和显式转换

需要与协议字段或寄存器宽度对应时，可以指定底层类型：

```cpp
#include <cstdint>

enum class ErrorCode : std::uint8_t {
    none = 0,
    invalidCommand = 1,
    invalidValue = 2,
    busy = 3
};
```

强类型枚举不会自动转换为整数。确实要输出协议值时，应显式转换：

```cpp
const auto raw = static_cast<std::uint8_t>(ErrorCode::busy);
```

这次转换发生在清楚的边界位置，而不是让整个程序都把错误码当普通整数。

### 示例2：解析结果

```cpp
enum class ParseResult : std::uint8_t {
    ok,
    emptyInput,
    unknownCommand
};

ParseResult validateCommand(std::string_view command)
{
    if (command.empty()) return ParseResult::emptyInput;
    if (command != "START" && command != "STOP") {
        return ParseResult::unknownCommand;
    }
    return ParseResult::ok;
}
```

调用者可以明确区分不同失败原因，而不是只得到`false`。

## 三、状态不是位标志

`idle`、`running`和`fault`表示设备当前只能处于其中一种状态，它们不应该按位组合。

位标志适合“多个能力可以同时成立”的情况：

```cpp
enum class Permission : std::uint8_t {
    none = 0,
    read = 1,
    write = 2,
    execute = 4
};
```

选学时可以显式转换后组合底层值。今天只需要会判断：如果值是互斥状态，就不要设计成位标志；如果多个开关可同时存在，才考虑位标志。

### 随堂练习2

判断下面哪些适合普通枚举，哪些可能适合位标志，并说明原因：

- 连接状态：未连接、连接中、已连接；
- 权限：可读、可写、可执行；
- 错误原因：超时、校验失败、参数非法。

## 重要错误提醒

1. 不要用`static_cast`绕过类型检查，把任意整数当合法状态；
2. 新增枚举值后要检查所有相关`switch`；
3. 状态和错误码即使底层数值相同，也不应互相赋值；
4. 互斥状态不应通过按位或组合。

## 代码题一：设备状态显示

定义`DeviceState`，包含`offline`、`idle`、`running`和`fault`。实现：

```cpp
std::string_view toString(DeviceState state);
bool canStart(DeviceState state);
```

只有`idle`可以启动。在`main()`中遍历或逐一测试全部状态。

## 代码题二：强类型错误码

定义底层类型为`std::uint8_t`的`CommandError`：成功、空输入、未知命令、参数非法。实现一个验证`START`、`STOP`和`SET RATE`的函数，返回具体错误码，并输出可读文本。

不要返回魔法整数，也不要在验证函数中直接打印。

## 快速自测

1. 为什么`enum class`比一组宏更不容易混用？
2. 枚举值`running`为什么通常要写成`DeviceState::running`？
3. 如何取得枚举对应的底层整数？
4. 什么时候需要指定`std::uint8_t`底层类型？
5. 设备当前状态适合做位标志吗？

## 今日小结

1. `enum class`把有限取值和类别放进类型系统；
2. 不同枚举类型不能直接混用；
3. 与协议交互时可以指定底层类型并在边界显式转换；
4. `switch`适合清楚处理有限状态；
5. 互斥状态与可组合位标志是两种不同模型。

## 算法副线

- 题目：14. Longest Common Prefix
- 难度：Easy
- 官方链接：[LeetCode 14](https://leetcode.com/problems/longest-common-prefix/)
- 建议时间：30分钟
- 训练目标：逐字符比较多个字符串的公共前缀
- 三级提示：[algorithms/day-012.md](../algorithms/day-012.md)

下一课开始学习`struct`与`class`，把数据和维护数据规则的函数放在一起。
