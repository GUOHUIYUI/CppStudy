# Day 7：Week 1复习、修错与周测

> 主线标准：C++17  
> C++主线预计用时：约90分钟  
> 算法题预计用时：25分钟  
> 前置：Day 1～Day 6；今天不学习新的C++主概念

## 今日范围

今天的目标不是继续增加知识点，而是检查前6天的内容能否脱离讲义独立使用。复习顺序固定为：先回忆，再修错，然后无提示重写，最后周测和记录。

今天必须达到：

- 能口头解释输入流恢复、引用方向、重载、默认参数和`constexpr`；
- 能识别“可以编译但行为错误”的代码；
- 能无提示重写一个带验证和引用输出的核心接口；
- 能写出包含预期值的测试，而不是只运行函数；
- Week 1周测达到80%后再进入Day 8。

今天暂时不要求：使用测试框架、异常、类、模板和复杂STL算法。

---

## 01：主动回忆检查

先关闭Day1～Day6讲义，用10分钟回答。每题先写答案，再打开讲义核对。

1. `std::cin`读取失败后，`clear()`和`ignore()`各解决什么问题？
2. `{}`初始化相比未初始化有什么直接价值？
3. `double& output`和`const double& input`分别表达什么接口方向？
4. 返回局部变量引用为什么会悬空？
5. 为什么只修改返回类型不能形成重载？
6. 默认参数为什么必须从右向左连续出现？
7. `inline`是否保证函数调用一定展开？
8. `constexpr`函数接收运行时变量时会发生什么？
9. 失败时不修改输出参数，应该怎样安排赋值顺序？
10. 编译通过是否能证明测试逻辑正确？

评分：每题1分。表述不必与讲义完全一致，但必须说明原因，而不是只写结论。

---

## 02：识别“能编译但不正确”

高警告等级只能发现一部分问题。下面这些代码往往可以编译，却仍然错误：

```cpp
double maximum(double left, double right);

// 拼写不同，调用double参数时可能转去调用int版本
double maximun(double left, double right);
```

```cpp
for (int value : numbers) {
    // value是元素本身，不一定是合法下标
    use(numbers[value]);
}
```

```cpp
void check(bool actual)
{
    std::cout << (actual ? "PASS" : "FAIL");
}
```

第三段只能检查“结果是否为真”，不能检查“结果是否符合预期”。如果某个非法参数本来就应该得到`false`，它反而会输出`FAIL`。

更合理的接口是：

```cpp
void checkBool(bool actual, bool expected)
{
    std::cout << (actual == expected ? "PASS" : "FAIL") << '\n';
}
```

测试必须同时包含实际结果和预期结果。

---

## 03：无提示重写核心接口

用25分钟，在空项目中无提示重写以下接口，不复制Day6代码：

```cpp
constexpr bool isCalibrationValid(
    double rawValue,
    double scale,
    double offset
);

constexpr double applyCalibration(
    double rawValue,
    double scale,
    double offset = 0.0
);

bool calibrate(
    double rawValue,
    double scale,
    double offset,
    double& result
);
```

完成后检查：

- `scale == 0`必须非法；
- 验证失败时`result`保持原值；
- 纯验证函数不输出文字；
- 纯计算函数不读取输入；
- 至少一条正常公式和三条边界规则能被`static_assert`验证。

如果第一次写错，保留错误版本的关键片段到错题记录中，再修正代码。

---

## 04：Week 1周测

周测总分10分，建议20分钟内完成：

1. 写出安全读取一个`double`的函数声明和失败处理关键代码。（2分）
2. 写出一个交换两个整数的引用函数，并解释为什么不用返回两个值。（1分）
3. 判断下面哪些构成重载并说明原因。（2分）

```cpp
int convert(int value);
double convert(double value);
double convert(int value);       // 与第一行的关系？
int convert(int value, int base);
```

4. 写出一个合法的默认参数声明和一个非法声明。（1分）
5. 写一个`constexpr`平方函数并使用`static_assert`验证。（1分）
6. 说明下面两个调用分别在何时计算。（1分）

```cpp
constexpr int a = square(4);
int input{};
std::cin >> input;
int b = square(input);
```

7. 为“输入必须大于0”的函数设计三个测试，至少包含一个边界和一个非法输入。（2分）

得分低于8分时，不需要重做整个Week 1，只补做失分对应的小节和代码。

---

## 05：错题与警告记录

建立简短记录，不需要复杂表格。每项写四行：

```text
问题：发生了什么
原因：我误解了什么
修正：最小正确改法
回练：准备在哪一天无提示再写一次
```

本周至少记录：

- 一个编译器警告；
- 一个编译通过但行为错误的问题；
- 一个测试设计错误；
- 一个算法题中不熟悉的C++语法。

记录的目的是形成可回练的问题列表，不是写长篇学习感想。

---

## 代码题一：修复失真的测试器

下面的测试器不能正确表示预期非法用例：

```cpp
void check(bool actual)
{
    std::cout << (actual ? "PASS" : "FAIL") << '\n';
}
```

请实现一组最小测试辅助函数，要求：

- 能比较`bool actual`与`bool expected`；
- 能比较`double actual`与`double expected`；
- 每个测试输出名称、实际值、预期值和`PASS/FAIL`；
- 使用它验证标定函数至少8组数据；
- 至少两组预期为失败；
- 单独验证失败时输出参数保持调用前的值。

<details>
<summary>提示</summary>

测试函数至少需要“实际值”和“预期值”两个参数。对于失败不修改输出，可以先给结果变量一个容易识别的值，例如`12345.0`，调用后再比较。

</details>

---

## 代码题二：无提示重写安全换算接口

实现一个温度换算接口：

```cpp
constexpr bool isCelsiusValid(double celsius);
constexpr double celsiusToFahrenheit(double celsius);
bool convertTemperature(double celsius, double& fahrenheit);
bool convertTemperature(int celsius, double& fahrenheit);
```

要求：

- 摄氏温度不能低于绝对零度`-273.15`；
- 非法时返回`false`且不修改输出；
- 整数重载必须复用浮点版本；
- 至少4条`static_assert`；
- 至少5组运行时测试，包含`-273.15`和一个非法值；
- 不读取输入、不输出错误信息的函数保持纯粹，交互放在`main()`。

<details>
<summary>提示</summary>

换算公式是`F = C × 9 / 5 + 32`。先验证，再计算到局部变量，最后写入引用输出参数。

</details>

---

## LeetCode 283：Move Zeroes

- 难度：Easy
- 主题：数组、双指针、原地修改
- 建议独立尝试：25分钟
- 官方链接：[LeetCode 283](https://leetcode.com/problems/move-zeroes/)
- 训练目标：区分“读取位置”和“写入位置”，保持非零元素相对顺序

题意摘要：把整数序列中的所有零移动到末尾，非零元素的相对顺序保持不变，并且必须直接修改原序列。

### 最小语法桥接

`std::vector<int>& nums`是对原容器的引用，对`nums[index]`赋值会修改调用者的数组。`std::size_t`是适合表示容器下标和大小的无符号整数类型：

```cpp
for (std::size_t index = 0; index < nums.size(); ++index) {
    std::cout << nums[index];
}
```

<details>
<summary>提示1</summary>

准备一个`write`位置，表示下一个非零元素应该写到哪里。

</details>

<details>
<summary>提示2</summary>

`read`遍历整个数组。遇到非零值时写入`nums[write]`，然后移动`write`。

</details>

<details>
<summary>提示3</summary>

所有非零元素写完后，从`write`开始把剩余位置全部填成0。

</details>

<details>
<summary>参考实现</summary>

```cpp
#include <cstddef>
#include <vector>

class Solution {
public:
    void moveZeroes(std::vector<int>& nums)
    {
        std::size_t write{};

        for (std::size_t read = 0; read < nums.size(); ++read) {
            if (nums[read] != 0) {
                nums[write] = nums[read];
                ++write;
            }
        }

        while (write < nums.size()) {
            nums[write] = 0;
            ++write;
        }
    }
};
```

时间复杂度：`O(n)`。  
额外空间复杂度：`O(1)`。

</details>

建议测试：

```text
[0,1,0,3,12] -> [1,3,12,0,0]
[0]           -> [0]
[1]           -> [1]
[0,0,0]       -> [0,0,0]
[1,2,3]       -> [1,2,3]
[0,1]         -> [1,0]
```

---

## Day 7完成标准

- 主动回忆题和周测均达到80%；
- 无提示重写标定核心接口；
- 修复测试器并完成至少8组有效测试；
- 错题记录包含警告、行为错误、测试错误和算法语法各一项；
- 独立尝试Move Zeroes并解释`read`与`write`的职责；
- 所有项目使用C++17高警告等级编译，无未解释警告；
- 未达到80%的部分进入补练清单，补齐后再开始Day 8。

