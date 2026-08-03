# Day 6：Week 1 综合练习——命令行标定工具 v1

> 主线标准：C++17  
> C++主线预计用时：约150分钟  
> 算法题预计用时：20分钟  
> 前置：Day 1～Day 5；今天不引入新的C++主知识点

## 今日范围

今天不继续堆语法，而是把已经学过的输入校验、引用、`const`、函数重载、默认参数、`constexpr`和`static_assert`组合起来，完成一个可测试的命令行标定工具。

标定模型统一使用：

```text
校准值 = 原始值 × 比例系数 + 偏移量
```

今天必须达到的目标：

- 能把输入、验证、计算、输出拆成不同职责；
- 能用`bool`返回操作是否成功，并只在成功时写入引用输出参数；
- 能设计不会发生歧义的重载；
- 能用`constexpr`与`static_assert`验证纯计算；
- 能设计至少8组正常、边界和非法测试。

今天暂时不展开：类、异常、单元测试框架、文件读写、`std::optional`和浮点误差算法。

---

## 01：先回忆，再开始编码

先不要看前几天的讲义，用5～10分钟回答：

1. 为什么读取失败后要同时调用`clear()`和`ignore()`？
2. `const double&`与`double&`分别向调用者表达什么承诺？
3. 为什么不能只靠返回类型区分重载？
4. `constexpr`函数是否只能接收编译期常量？
5. 默认参数为什么必须从右侧开始连续出现？

答不上来的问题做上标记即可，不要先抄答案。完成今天的程序后再回来重新回答。

---

## 02：先确定数据规则

一个计算函数是否可靠，首先取决于它有没有明确的输入边界。今天规定：

- 原始值`rawValue`必须处于`-100000～100000`；
- 比例系数`scale`必须大于0且不超过1000；
- 偏移量`offset`必须处于`-100000～100000`；
- 验证失败时返回`false`，不得修改调用者原来的结果；
- 验证成功时才计算并写入结果。

纯计算可以单独写成：

```cpp
constexpr double applyCalibration(
    double rawValue,
    double scale,
    double offset = 0.0)
{
    return rawValue * scale + offset;
}

static_assert(applyCalibration(100.0, 0.5, 2.0) == 52.0,
              "calibration formula failed");
```

验证规则和计算公式不要混在输入代码中。这样公式既能被编译期测试，也能被命令行程序复用。

---

## 03：输入校验形成固定模板

`operator>>`读取失败后，错误状态会保留。只调用`clear()`会解除错误状态，但非法字符仍留在输入缓冲区；只调用`ignore()`又无法恢复流状态。因此两步缺一不可。

```cpp
bool readDouble(const std::string& prompt, double& value)
{
    std::cout << prompt;

    if (std::cin >> value) {
        return true;
    }

    std::cin.clear();
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );
    return false;
}
```

这里的`prompt`是只读输入，`value`是输出参数。失败时函数没有给`value`赋新值。

今天可以为`int`再写一个同名版本：

```cpp
bool readValue(const std::string& prompt, int& value);
bool readValue(const std::string& prompt, double& value);
```

第二个参数类型不同，因此构成清晰重载。不要再增加一组依赖默认参数、会让同一调用同时匹配的版本。

---

## 04：引用和`const`表达接口方向

推荐把标定操作写成：

```cpp
bool calibrate(
    double rawValue,
    double scale,
    double offset,
    double& calibratedValue
);
```

前三个参数是很小的数值类型，直接按值传递即可；给值参数写`const`只约束函数内部的局部副本，不会增强调用者看到的接口承诺。

最后一个参数是非`const`引用，明确表示函数可能修改调用者的对象。正确的实现顺序应当是：

1. 验证所有参数；
2. 任意参数非法就立即返回`false`；
3. 使用局部变量完成计算；
4. 最后一次性给`calibratedValue`赋值并返回`true`。

这样能保证失败时输出参数保持不变。

---

## 05：重载与默认参数只解决真实需求

可以提供一个整数原始值重载：

```cpp
bool calibrate(
    int rawValue,
    double scale,
    double offset,
    double& calibratedValue
);
```

它可以把`rawValue`转换成`double`后复用核心版本。调用`calibrate(100, ...)`时会精确匹配整数版本，调用`calibrate(100.5, ...)`时会匹配浮点版本。

默认参数只放在纯计算函数的`offset`上即可。不要同时再添加：

```cpp
// 容易与其他版本重叠，不建议
// bool calibrate(double raw, double scale,
//                double& result, double offset = 0.0);
```

接口越多不代表设计越好。今天的目标是每种常见调用只有一个明显候选。

---

## 06：测试先覆盖行为，再追求数量

至少完成下面8组测试：

| 编号 | 输入 | 预期 |
|---:|---|---|
| 1 | `100, 0.5, 2` | 成功，结果`52` |
| 2 | `0, 1, 0` | 成功，结果`0` |
| 3 | `-100000, 1, 0` | 成功，测试原始值下边界 |
| 4 | `100000, 1, 0` | 成功，测试原始值上边界 |
| 5 | `100001, 1, 0` | 失败，结果保持原值 |
| 6 | `100, 0, 0` | 失败，比例系数非法 |
| 7 | `100, 1000, -100000` | 成功，测试合法边界 |
| 8 | 命令行输入`abc` | 读取失败，程序能够继续或正常结束 |

不要只输出结果让人眼检查。可以写一个小的`checkEqual`或`checkNear`函数，输出每项测试的`PASS/FAIL`。今天允许直接比较由简单十进制数产生的结果；更系统的浮点误差比较以后再学。

---

## 代码题一：标定函数组

实现以下函数：

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
    double& calibratedValue
);

bool calibrate(
    int rawValue,
    double scale,
    double offset,
    double& calibratedValue
);
```

要求：

- 使用至少4条`static_assert`验证规则和公式；
- 两个`calibrate`版本不能复制整套验证与计算逻辑；
- 失败时不得修改`calibratedValue`；
- 自己补充正常值、边界值和非法值测试。

<details>
<summary>提示</summary>

先让`double`版本成为唯一核心实现。整数版本只负责转换后转交。先计算到局部变量，确认成功后再写输出参数。

</details>

---

## 代码题二：命令行传感器标定工具 v1

编写一个完整命令行程序：

1. 依次读取原始值、比例系数和偏移量；
2. 任意输入不是数字时给出明确错误信息；
3. 输入格式正确后调用`calibrate`，不得在`main()`重复公式；
4. 参数越界时说明是哪一类参数非法；
5. 成功时输出原始值、参数和最终结果；
6. 程序中运行或单独提供至少8组测试。

验收重点不是界面漂亮，而是输入失败、业务验证失败和计算成功三条路径互不混淆。

<details>
<summary>提示1：组织顺序</summary>

先完成并测试纯函数，再写输入函数，最后写`main()`。不要从交互界面开始堆代码。

</details>

<details>
<summary>提示2：错误分类</summary>

输入`abc`属于“读取失败”；输入比例系数`0`属于“读取成功但业务参数非法”。这两类错误应分别处理。

</details>

---

## LeetCode 217：Contains Duplicate

- 难度：Easy
- 主题：数组、集合
- 建议独立尝试：20分钟
- 官方链接：[LeetCode 217](https://leetcode.com/problems/contains-duplicate/)
- 训练目标：从双重循环过渡到“记录已经见过的值”

题意摘要：给定一个整数序列，只要某个数至少出现两次就返回`true`，所有值都只出现一次则返回`false`。

### 当前知识可以完成的方案

你完全可以先使用双重`for`循环：固定一个元素，再检查它后面的每个元素。这个方案时间复杂度为`O(n²)`、额外空间复杂度为`O(1)`，逻辑正确，是本题合格的第一版。

### 最小语法桥接：`std::unordered_set`

哈希集合只保存“不重复的键”：

```cpp
#include <unordered_set>

std::unordered_set<int> seen;
seen.insert(42);       // 插入
seen.count(42);        // 存在时为1，不存在时为0
```

今天只要求会用这两个操作，不要求理解哈希表的内部实现。

<details>
<summary>提示1</summary>

遍历每个数字之前，先检查它是否已经存在于`seen`中。

</details>

<details>
<summary>提示2</summary>

如果已经存在，可以立即返回`true`；否则把它插入集合并继续。

</details>

<details>
<summary>提示3</summary>

如果整个循环结束都没有提前返回，说明没有重复值。

</details>

<details>
<summary>参考实现</summary>

```cpp
#include <unordered_set>
#include <vector>

class Solution {
public:
    bool containsDuplicate(std::vector<int>& nums)
    {
        std::unordered_set<int> seen;

        for (int value : nums) {
            if (seen.count(value) != 0) {
                return true;
            }

            seen.insert(value);
        }

        return false;
    }
};
```

平均时间复杂度：`O(n)`。  
额外空间复杂度：`O(n)`。

哈希表在极端冲突情况下存在更差表现；现阶段按平均复杂度理解即可。

</details>

建议测试：

```text
[1, 2, 3, 1] -> true
[1, 2, 3, 4] -> false
[1, 1]       -> true
[]           -> false
[-1, -2, -1] -> true
```

---

## Day 6完成标准

- 无提示解释Day1～Day5五个回忆问题；
- 完成两个标定重载，并保证失败不修改输出参数；
- 至少4条`static_assert`通过；
- 命令行工具能区分读取失败、参数非法和计算成功；
- 至少8组标定测试全部通过，并记录失败原因；
- LeetCode 217先独立尝试，再记录方案的时间与空间复杂度；
- 最后写3～5句话复盘：今天最容易混淆的接口、一次编译警告、一个准备在Day7重写的部分。

