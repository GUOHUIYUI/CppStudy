# Day 5：函数重载、默认参数、`inline` 与 `constexpr`

> 主线标准：C++17  
> 预计用时：约135分钟  
> 前置：Day 2类型与转换、Day 4 `const`

## 今日范围

今天学习如何为一组相关操作设计清晰的函数接口。C++允许多个函数共用同一名称，但只有在参数语义清楚、调用不歧义时，重载才会让代码更好。

今天必须掌握：

- 通过参数列表区分重载函数；
- 知道返回类型不能单独构成重载；
- 正确设计默认参数；
- 理解`inline`不是强制性能优化命令；
- 使用`constexpr`函数和`static_assert`完成编译期验证。

今天暂时不展开：函数模板、完美转发、复杂重载解析规则和类成员重载。

---

## 01：为什么需要函数重载

C语言中常用不同函数名处理不同类型：

```cpp
int maximumInt(int left, int right);
double maximumDouble(double left, double right);
```

C++可以让相同语义共用名称：

```cpp
int maximum(int left, int right)
{
    return left > right ? left : right;
}

double maximum(double left, double right)
{
    return left > right ? left : right;
}
```

调用时，编译器根据实参类型选择函数：

```cpp
maximum(10, 20);      // 调用int版本
maximum(1.5, 2.5);    // 调用double版本
```

重载的价值是统一相同操作的名称，不是为了展示语法技巧。

---

## 02：重载规则与解析

重载函数必须在参数列表上有区别：

```cpp
int sum(int a, int b);
int sum(int a, int b, int c);       // 参数数量不同
double sum(double a, double b);     // 参数类型不同
```

下面不能构成重载：

```cpp
// int parse();
// double parse(); // 错误：只有返回类型不同
```

原因是调用者可以忽略返回值：

```cpp
parse();
```

编译器无法从这句话判断应该选择哪个版本。

重载解析会优先选择更精确的匹配。当多个版本都需要类似的隐式转换时，可能产生歧义。现阶段的设计原则是：

> 让每个常见调用都有明显的唯一选择。

---

## 03：默认参数

默认参数允许调用者省略常用值：

```cpp
double finalPrice(
    double unitPrice,
    int quantity = 1,
    double discount = 1.0
)
{
    return unitPrice * quantity * discount;
}
```

调用方式：

```cpp
finalPrice(19.9);          // quantity=1, discount=1.0
finalPrice(19.9, 3);       // discount=1.0
finalPrice(19.9, 3, 0.8);  // 全部显式提供
```

默认参数必须从右向左连续出现：

```cpp
// void configure(int timeout = 100, int retries); // 错误
void configure(int timeout, int retries = 3);      // 正确
```

在多文件工程中，默认值通常只写在头文件的声明中，定义处不重复书写。

---

## 04：`inline`函数

```cpp
inline bool isPositive(int value)
{
    return value > 0;
}
```

`inline`在现代C++中有两个需要区分的含义：

1. 它允许同一个函数定义出现在多个翻译单元中，常用于头文件中的短函数；
2. 它不保证编译器把函数调用替换成函数体。

是否真正内联是编译器的优化决定。不要为了“提速”给所有函数加`inline`。

在类内直接定义的成员函数默认具有内联语义，后面学习类时会再见到。

---

## 05：`constexpr`函数与`static_assert`

`constexpr`函数在条件满足时可以在编译期求值：

```cpp
constexpr int square(int value)
{
    return value * value;
}

static_assert(square(5) == 25, "square calculation failed");
```

`static_assert`在编译期检查条件。如果条件为假，程序无法通过编译。

`constexpr`函数也可以处理运行时数据：

```cpp
int input{};
std::cin >> input;
std::cout << square(input) << '\n';
```

这次调用的`input`在运行时才知道，所以计算在运行时完成。

> `constexpr`表示“允许在编译期计算”，不表示“所有调用都强制发生在编译期”。

---

## 06：常见歧义与设计边界

### 默认参数与重载冲突

```cpp
void print(int value);
void print(int value, int base = 10);

// print(42); // 歧义：两个函数都能匹配
```

不要让默认参数和重载同时为同一调用提供候选。

### 不要让类型暗中改变语义

如果`convert(100)`表示厘米，而`convert(100.0)`表示英里，这种重载虽然可以编译，但很容易误用。重载各版本应该表达同一种概念操作。

### 只为真实需求设计重载

函数名不同本身不是问题。`metersToKilometers`和`celsiusToFahrenheit`往往比一组语义模糊的`convert`更好。

---

## 常见错误

- 只改返回类型，误以为形成重载；
- 重载版本过多，导致隐式转换歧义；
- 默认参数不从右侧开始；
- 在函数声明和定义中重复指定默认值；
- 认为`inline`一定能提高性能；
- 认为`constexpr`函数不能接收运行时数据；
- 只写`constexpr`却不用`static_assert`验证。

---

## 代码题一：重载数学工具库

实现：

```cpp
constexpr int maximum(int left, int right);
constexpr double maximum(double left, double right);
constexpr int sum(int a, int b);
constexpr int sum(int a, int b, int c);
```

要求：

- 不使用`std::max`；
- 四个函数都应可以参与编译期计算；
- 使用至少4条`static_assert`验证整数、浮点数、负数和相等值；
- 在`main()`中用运行时输入再测试一次。

建议测试：

```text
maximum(3, 7)
maximum(-2.5, -8.0)
maximum(4, 4)
sum(1, 2)
sum(1, 2, 3)
```

<details>
<summary>提示</summary>

每个函数只需一个简单表达式。`static_assert`必须放在可以编译期求值的位置，不能使用`std::cin`读取的值。

</details>

---

## 代码题二：订单价格函数

实现：

```cpp
inline bool isValidOrder(
    double unitPrice,
    int quantity,
    double discount
);

constexpr double finalPrice(
    double unitPrice,
    int quantity = 1,
    double discount = 1.0
);
```

要求：

- 单价不能为负；
- 数量必须是`0～100000`；
- 折扣必须处于`0～1`；
- 分别测试只传单价、传单价与数量、传全部参数；
- 非法输入不得进入价格计算；
- 使用`static_assert`验证至少一个固定价格。

建议测试：

```text
finalPrice(10.0)
finalPrice(10.0, 3)
finalPrice(10.0, 3, 0.8)
单价 -1
数量 100001
折扣 1.2
```

<details>
<summary>提示</summary>

`constexpr`负责纯计算，`isValidOrder`负责验证。不要在`finalPrice`中读取输入或输出文字。

</details>

---

## LeetCode 242：Valid Anagram

- 难度：Easy
- 主题：字符串、计数
- 建议独立尝试：25分钟
- 链接：[LeetCode 242](https://leetcode.com/problems/valid-anagram/)

题意摘要：判断两个字符串是否包含完全相同的字符及出现次数，字符顺序可以不同。

### 最小语法桥接

```cpp
std::string s;
s.size();
s[index];
```

`std::string`可以暂时当作自动管理长度的字符数组。本题已经说明输入为小写英文字母，可以用固定长度26的计数数组。

<details>
<summary>提示1</summary>

如果两个字符串长度不同，可以立即返回`false`。

</details>

<details>
<summary>提示2</summary>

字符`'c'`可以映射到下标：

```cpp
const int index = 'c' - 'a';
```

因此`'a'`对应0，`'z'`对应25。

</details>

<details>
<summary>提示3</summary>

遍历第一个字符串时加一，遍历第二个字符串时减一。最后所有计数都应该为0。

</details>

<details>
<summary>参考实现</summary>

```cpp
#include <string>

class Solution {
public:
    bool isAnagram(std::string s, std::string t)
    {
        if (s.size() != t.size()) {
            return false;
        }

        int counts[26]{};

        for (char current : s) {
            ++counts[current - 'a'];
        }

        for (char current : t) {
            --counts[current - 'a'];
        }

        for (int count : counts) {
            if (count != 0) {
                return false;
            }
        }

        return true;
    }
};
```

时间复杂度：`O(n)`。  
额外空间复杂度：`O(1)`，因为计数数组固定为26个元素。

</details>

---

## Day 5完成标准

- 能说明函数重载是由参数列表区分，不是由返回类型区分；
- 能识别默认参数与重载造成的歧义；
- 能解释`inline`不保证真正内联；
- 能编写`constexpr`函数并用`static_assert`验证；
- 独立完成两道代码题；
- 独立尝试Valid Anagram并记录时间、空间复杂度。
