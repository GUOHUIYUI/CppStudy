# Day 17：让错误信息说清楚发生了什么

> 所属阶段：C++基础迁移（Week 3）
> 正课必修：约120～145分钟
> 巩固与选学：约20～35分钟
> LeetCode：30分钟，单独计算
> 前置：Day 12强类型枚举、Day 16命名空间与多文件组织

到目前为止，许多函数用`bool`表示成功或失败。这对“只有一种失败原因”的小函数足够，但解析配置时，调用者通常还想知道：哪个字段错了、为什么错、应该怎样提示用户。

今天解决一个核心问题：怎样用显式返回状态表达可预期的解析失败，同时认识异常适合处理哪一类问题？

## 学习目标

完成必修后，你应该能够：

1. 解释`bool`为什么无法区分多种失败原因；
2. 使用`enum class`定义清晰的错误码；
3. 设计并返回包含错误码、字段和原因的`ParseResult`；
4. 保证解析失败时不修改调用者原有数据；
5. 知道错误码与异常的基本使用边界。

## 今天的内容边界

### 必修

- `bool`、错误码和结果结构体的表达能力；
- `ParseResult`的基本设计；
- 先验证、成功后再提交修改；
- 调用者根据结果决定提示或继续处理；
- `throw`、`try`和`catch`的概览。

### 巩固

- 把错误码转换为可读文本；
- 区分“可预期输入错误”和“无法在当前层处理的失败”；
- 避免用异常代替普通分支。

### 选学

- `std::error_code`、`std::optional`、`std::variant`和`std::expected`；
- 异常传播、栈展开和异常安全保证；
- 禁用异常的嵌入式环境如何统一错误模型。

今天不展开异常安全、RAII和栈展开细节。它们会在资源管理阶段系统学习。

## 一、`bool`只告诉你成败

下面的接口很简单：

```cpp
bool parseRate(std::string_view text, int& rate);
```

调用者可以判断失败，却无法直接知道失败原因：

- 输入为空；
- 包含非数字字符；
- 数值超出范围。

如果所有失败都只打印“invalid input”，程序虽然能工作，却很难给用户准确提示。把打印写进`parseRate`也不理想，因为解析函数随后就难以被命令行、测试程序和图形界面共同复用。

第一步是定义错误码：

```cpp
enum class ParseError {
    none,
    emptyInput,
    invalidNumber,
    outOfRange
};
```

`ParseError`让调用者能够区分失败类型。`enum class`不会随意与整数混用，也能避免全局枚举名冲突。

## 二、用结果对象一起返回状态和数据

C++17还没有标准库`std::expected`，基础阶段可以使用普通结构体：

```cpp
#include <string>

enum class ParseError {
    none,
    emptyInput,
    invalidNumber,
    outOfRange
};

struct ParseResult {
    ParseError error{ParseError::none};
    int value{};
    std::string field;
    std::string reason;

    bool succeeded() const
    {
        return error == ParseError::none;
    }
};
```

这不是一个需要设计得很复杂的“企业结果框架”。它只是把本次解析的几项直接结果放在一起：

- `error`供程序判断；
- `value`只在成功时使用；
- `field`指出错误字段；
- `reason`用于显示或记录。

### 示例1：解析采样率

```cpp
#include <charconv>
#include <string_view>

ParseResult parseRate(std::string_view text)
{
    if (text.empty()) {
        return {ParseError::emptyInput, 0, "rate", "value is empty"};
    }

    int value{};
    const char* first = text.data();
    const char* last = text.data() + text.size();
    const auto result = std::from_chars(first, last, value);

    if (result.ec != std::errc{} || result.ptr != last) {
        return {ParseError::invalidNumber, 0, "rate", "use decimal digits only"};
    }
    if (value < 1 || value > 1000) {
        return {ParseError::outOfRange, 0, "rate", "expected 1 to 1000"};
    }

    return {ParseError::none, value, "rate", ""};
}
```

`std::from_chars`把字符区间转换为整数。今天只需观察它的两个结果：

- `ec`表示转换是否出现错误；
- `ptr == last`表示整个输入都被消费，避免把`"100abc"`误当成`100`。

调用者可以统一处理：

```cpp
const ParseResult result = parseRate(input);

if (!result.succeeded()) {
    std::cout << result.field << ": " << result.reason << '\n';
} else {
    config.setRate(result.value);
}
```

解析函数不直接修改`config`。只有结果成功后，调用者才提交新值。

### 随堂练习1

给`ParseError`增加`unsupportedValue`，并编写`parseMode`：只接受`"AUTO"`、`"MANUAL"`和`"SAFE"`。分别观察空输入和不支持的模式返回了什么字段与原因。

## 三、失败时保持原值

输出参数并没有错，但要把修改时机放对：

```cpp
bool parseRate(std::string_view text, int& rate)
{
    int candidate{};

    // 所有解析和范围检查都写入candidate
    // ...

    rate = candidate; // 只有全部成功后才修改输出
    return true;
}
```

如果函数一边读取字符一边直接修改`rate`，后续遇到非法字符时，函数虽然返回`false`，调用者的数据却已经变了一部分。这会让“失败”变得难以理解。

结果对象通常更直观：失败结果根本不需要写入调用者对象，成功分支再应用`result.value`。

### 示例2：命令解析结果包含字段和原因

```cpp
enum class CommandStatus {
    ok,
    emptyInput,
    unknownCommand,
    missingArgument,
    invalidArgument
};

struct CommandResult {
    CommandStatus status{CommandStatus::ok};
    std::string field;
    std::string reason;

    bool succeeded() const
    {
        return status == CommandStatus::ok;
    }
};
```

处理`RATE abc`时可以返回：

```cpp
return {
    CommandStatus::invalidArgument,
    "rate",
    "use an integer from 1 to 1000"
};
```

处理`RATE`时则可以返回：

```cpp
return {
    CommandStatus::missingArgument,
    "rate",
    "RATE requires one value"
};
```

两次都失败，但调用者得到了不同的信息。`main()`负责决定是打印、记录，还是稍后在其他界面中显示；解析模块只负责描述结果。

### 随堂练习2

为`NAME`命令设计三种结果：成功、缺少名称、名称超过16字符。先写出每种结果中的`status`、`field`和`reason`，再实现分支。确认失败时原名称不变。

## 四、什么时候考虑异常

异常的最小语法如下：

```cpp
#include <stdexcept>

void loadRequiredFile(bool available)
{
    if (!available) {
        throw std::runtime_error("required file is unavailable");
    }
}

int main()
{
    try {
        loadRequiredFile(false);
    } catch (const std::runtime_error& error) {
        std::cout << error.what() << '\n';
    }
}
```

`throw`把控制转移到能够匹配的`catch`。异常可以跨过多个调用层传播，因此适合当前函数无法正常处理、又不希望每层都机械转发的失败。

但命令行用户输入错误是正常、可预期的业务分支：用户输入`RATE abc`后，程序提示并允许重试即可。用显式`ParseResult`通常更容易看到控制流，也更适合当前课程阶段。

先使用下面的简单判断：

| 情况 | 当前阶段的优先选择 |
|---|---|
| 用户输入格式错误 | 返回状态或结果对象 |
| 查找结果可能不存在 | 显式返回状态；后续学习`optional` |
| 当前层可以立即恢复 | 正常分支处理 |
| 深层操作无法继续，调用者统一处理 | 可以考虑异常 |
| 禁用异常的平台 | 错误码或结果对象 |

这不是永远不变的规则。Day39会结合RAII、栈展开和异常保证重新比较两种接口。

## 重要错误提醒

1. 不要在校验完成前修改调用者原有数据；
2. 成功状态与错误信息要保持一致，不能返回`ok`同时附带失败原因；
3. 结果中的`value`只在成功时使用，不要依赖失败结果里的占位值；
4. 不要把普通的用户输入错误全部改成异常。

## 代码题一：显式的采样率解析结果

在`01_显式解析结果`中实现`ParseError`、`ParseResult`和`parseRate(std::string_view)`。

需要覆盖：

- 空输入；
- 非数字或只解析了一部分的输入；
- 小于1或大于1000；
- 合法边界1和1000。

每次输出成功状态；失败时输出字段和原因，成功时输出解析值。不要用异常处理这些输入。

## 代码题二：配置解析错误详情

在`02_配置解析错误详情`中建立`parse_result.h`、`parse_result.cpp`和`main.cpp`，把Day16配置器的命令结果改为包含：

```text
status + field + reason
```

至少处理`NAME`、`RATE`和未知命令。关键行为是：

- 缺少参数与非法参数可以区分；
- 错误指出对应字段；
- 失败时配置保持原值；
- `main()`统一显示错误，不在每个解析分支里直接打印。

不要求把整个Day14配置器全部复制过来；聚焦错误返回即可。

## 快速自测

1. `bool`返回值为什么难以表达三种不同失败原因？
2. 错误码和给用户看的原因文本分别服务于谁？
3. 为什么应该先写入局部候选值，再修改输出参数？
4. 失败的`ParseResult`中的解析值是否应该继续使用？
5. `RATE abc`更适合显式结果还是异常？为什么？

## 今日小结

1. `bool`适合简单成败，多种失败原因应使用明确错误码；
2. 结果对象可以一起携带状态、值、字段和原因；
3. 先完成验证，再修改调用者数据；
4. 显示错误是调用者的职责，解析函数负责描述错误；
5. 异常适合无法在当前层正常处理的失败，不替代普通输入分支。

## 算法副线

- 题目：268. Missing Number
- 难度：Easy
- 官方链接：[LeetCode 268](https://leetcode.com/problems/missing-number/)
- 建议时间：30分钟
- 训练目标：比较求和、异或与排序方案对边界和溢出的影响
- 三级提示：[algorithms/day-017.md](../algorithms/day-017.md)

下一课将学习构造函数、成员初始化列表和析构函数概念，让对象从创建时就进入合法状态。
