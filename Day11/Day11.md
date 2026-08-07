# Day 11：从 C 字符串到 `std::string` 与 `std::string_view`

> 所属阶段：C++基础迁移（Week 2）  
> 正课必修：约130～150分钟  
> 巩固与选学：约20～40分钟  
> LeetCode：20分钟，单独计算  
> 前置：Day 8对象生命周期、Day 10数组与范围`for`

今天解决一个实际问题：怎样在C++中安全、清楚地表示“拥有一段文本”和“只借用一段文本”？

## 学习目标

完成必修后，你应该能够：

1. 说明C字符串为何依赖结尾的`'\0'`；
2. 使用`std::string`创建、拼接、比较和读取文本；
3. 使用`std::string_view`表达不拥有文本的只读视图；
4. 避免让`string_view`指向已经销毁或已经变化的字符串；
5. 用字符串操作实现一个小型串口命令解析器。

## 内容边界

### 必修

- C字符数组与`'\0'`；
- `std::string`的值语义、`size()`、比较、查找和子串；
- `std::string_view`的只读借用语义；
- 最常见的生命周期错误。

### 巩固

- `empty()`、`find()`、`substr()`；
- `std::getline`读取带空格的一整行；
- 解析`SET RATE 100`这一类简单命令。

### 选学

- 小字符串优化和具体内存布局；
- `char8_t`、Unicode编码转换和正则表达式；
- 完整协议解析器与零拷贝设计。

今天不讲动态内存管理，也不把`string_view`当作性能优化万能答案。

## 一、C字符串的边界来自终止字符

```cpp
char command[]{'R', 'U', 'N', '\0'};
```

字符数组的容量是4，但文本长度是3。许多C字符串函数会一直读取，直到遇到`'\0'`；遗漏终止字符可能导致越界读取。

### 示例1：数组容量与文本长度

```cpp
#include <cstring>
#include <iostream>

int main()
{
    char command[8]{"RUN"};
    std::cout << "capacity = " << sizeof(command) << '\n';
    std::cout << "length = " << std::strlen(command) << '\n';
}
```

预期输出：

```text
capacity = 8
length = 3
```

`sizeof`回答数组占多少字节，`strlen`回答第一个`'\0'`之前有多少字符。两者不是一回事。

### 随堂练习1

把`command`改为`"STATUS"`，先预测容量和长度，再运行。然后解释为什么容量仍是8。

## 二、`std::string`拥有自己的文本

`std::string`负责保存字符序列，能够直接复制、赋值、比较和拼接：

```cpp
#include <iostream>
#include <string>

int main()
{
    std::string command{"SET"};
    command += " RATE";
    command += " 100";

    std::cout << command << '\n';
    std::cout << "length = " << command.size() << '\n';
    std::cout << std::boolalpha << (command == "SET RATE 100") << '\n';
}
```

复制一个`std::string`会得到可以独立存在的字符串对象。至于它内部怎样申请和释放内存，留到RAII与动态内存阶段再深入。

常用操作：

```cpp
text.empty();
text.size();
text.find(' ');
text.substr(0, 3);
```

`find`找不到时返回`std::string::npos`，不能把“找不到”误当成下标0。

### 示例2：拆出命令名和参数

```cpp
#include <iostream>
#include <string>

int main()
{
    const std::string line{"MODE AUTO"};
    const std::size_t separator{line.find(' ')};

    if (separator == std::string::npos) {
        std::cout << "command only\n";
        return 0;
    }

    const std::string name{line.substr(0, separator)};
    const std::string argument{line.substr(separator + 1)};
    std::cout << "name = " << name << '\n';
    std::cout << "argument = " << argument << '\n';
}
```

这里的`name`和`argument`各自拥有字符。即使`line`之后被修改，它们也不会跟着变化。

## 三、`std::string_view`只借用文本

`std::string_view`保存的是一段字符的位置和长度，不拥有字符：

```cpp
#include <iostream>
#include <string_view>

bool isKnownCommand(std::string_view command)
{
    return command == "RUN" || command == "STOP" || command == "STATUS";
}
```

它可以查看字符串字面量、字符数组或仍然存活的`std::string`。适合“函数只读，而且不需要保存参数”的接口。

```cpp
std::string command{"RUN"};
std::cout << isKnownCommand(command) << '\n';
```

最重要的规则是：视图不能比它指向的字符活得更久。

```cpp
std::string_view badView()
{
    std::string local{"RUN"};
    return local; // 错误：返回后local被销毁
}
```

这段代码用于识别错误，不要运行或照抄到项目中。

### 随堂练习2

实现：

```cpp
bool hasPrefix(std::string_view text, std::string_view prefix);
```

当前还不使用C++20的`starts_with`。先判断长度，再逐个比较前缀字符。测试空前缀、相等字符串和前缀过长三种情况。

## 四、串口命令解析器 v1

本日只解析三个固定命令：

```text
START
STOP
SET RATE 100
```

解析器先把输入按值保存在`std::string`中，然后只在一次函数调用期间用`std::string_view`读取。暂不保存视图，不处理引号、转义、Unicode或任意数量参数。

建议接口：

```cpp
bool parseCommand(std::string_view line, std::string& name, std::string& argument);
```

规则：

- 空串失败；
- 输入长度超过64失败；
- 没有空格时，整行是命令名，参数为空；
- 有空格时，第一段是命令名，其余部分是参数；
- 命令名只能是`START`、`STOP`或`SET`；
- 失败时不修改两个输出字符串。

先完成全部验证，再一次性写入输出，这与此前“失败时输出不变”的练习相呼应。

## 重要错误提醒

1. 字符数组有容量，不代表其中一定存在合法的`'\0'`结尾字符串；
2. `find`失败返回`npos`，不能直接拿结果做`separator + 1`；
3. 从局部`std::string`返回`string_view`会产生悬空视图；
4. 修改原字符串可能让已有视图失效，今天不要跨修改保存视图。

## 代码题一：文本统计器

实现一个函数，接收`std::string_view`，统计：

- 字符总数；
- 空格数量；
- 数字字符数量。

在`main()`中验证空串、普通文本和仅含数字的文本。只需处理ASCII字符。

## 代码题二：串口命令解析器 v1

在对应项目中实现前述`parseCommand`。至少亲自运行：

- 空串；
- `START`；
- `SET RATE 100`；
- 未知命令；
- 超过64字符的输入。

输出每个案例的成功状态、命令名和参数，以便观察失败时输出是否保持不变。

## 快速自测

1. C字符串如何确定文本终点？
2. `std::string`复制后，新对象是否依赖原对象继续存活？
3. `std::string_view`是否拥有字符？
4. `find`找不到分隔符时返回什么？
5. 为什么不能返回指向局部`std::string`的视图？

## 今日小结

1. C字符串依赖`'\0'`，数组容量与文本长度不同；
2. `std::string`拥有文本，适合保存和修改；
3. `std::string_view`只借用文本，适合短期只读访问；
4. 使用视图时必须保证被查看字符仍然存活；
5. 简单解析也应先验证，再修改输出。

## 算法副线

- 题目：344. Reverse String
- 难度：Easy
- 官方链接：[LeetCode 344](https://leetcode.com/problems/reverse-string/)
- 建议时间：20分钟
- 训练目标：使用双指针原地交换字符
- 三级提示：[algorithms/day-011.md](../algorithms/day-011.md)

下一课将使用`enum class`表达有限状态与错误码，减少宏常量和任意整数混用。
