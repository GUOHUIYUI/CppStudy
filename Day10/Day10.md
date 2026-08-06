# Day 10：原生数组、`std::array`与范围`for`

> 所属阶段：C++基础迁移（Week 2）  
> 正课必修：约120～160分钟  
> 巩固与选学：约20～40分钟  
> LeetCode：25分钟，单独计算  
> 前置：Day 2类型与初始化、C语言数组基础  
> 后续：Day 11学习C字符串、`std::string`与`std::string_view`

今天围绕一个问题展开：

> 当数据数量在编译时已经固定，C++怎样比传统原生数组更清楚地保存尺寸、遍历元素并减少越界风险？

原生数组仍然是C++的一部分，但`std::array`把“固定数量的一组元素”包装成了更容易传递和使用的对象。今天会从熟悉的C数组出发，逐步改写为`std::array`，再使用范围`for`完成读取和修改。

## 今日学习目标

完成必修部分后，你应该能够：

1. 正确声明、列表初始化和按下标访问原生数组；
2. 说明原生数组传入函数后为什么通常需要额外传递长度；
3. 使用`std::array<T, N>`保存固定数量的数据，并调用`size()`；
4. 使用范围`for`读取元素，并使用引用修改元素；
5. 区分`operator[]`与`at()`的边界检查特点。

## 今天的内容边界

### 必修

- 原生数组的初始化、下标和尺寸；
- `std::array`的声明、初始化、下标和`size()`；
- 范围`for`的值访问与引用访问；
- 固定数组的基本边界风险。

### 巩固

- 原生数组作为函数参数时的尺寸丢失；
- `front()`、`back()`和`at()`；
- 使用`const std::array<...>&`只读传参。

### 选学

- C++20的`std::span`只作为“连续数据视图”认识，不要求编写；
- `std::vector`、迭代器和通用模板函数将在后续课程系统学习。

---

## 一、从原生数组开始

原生数组把相同类型的多个对象连续排列。它的元素数量必须在声明时确定：

```cpp
int values[5]{3, 1, 4, 1, 5};
```

下标从0开始，因此这里的合法下标是0到4。

```cpp
std::cout << values[0] << '\n';
std::cout << values[4] << '\n';
```

访问`values[5]`已经越过数组边界。原生数组的`operator[]`不会自动检查下标，越界访问属于未定义行为。

### 示例1：原生数组的尺寸与遍历

```cpp
#include <iostream>
#include <iterator>

int main()
{
    int values[5]{3, 1, 4, 1, 5};
    int sum{};

    for (std::size_t index{}; index < std::size(values); ++index) {
        sum += values[index];
    }

    std::cout << "count = " << std::size(values) << '\n';
    std::cout << "sum = " << sum << '\n';
    return 0;
}
```

预期输出：

```text
count = 5
sum = 14
```

`std::size(values)`在数组声明所在的作用域中能够得到元素数量。它比手写`sizeof(values) / sizeof(values[0])`更直接。

但原生数组传入函数时通常会退化成指针：

```cpp
void printValues(const int values[], std::size_t count);
```

函数参数中的`values`不能自行保留原数组的元素数量，所以还需要`count`。这正是`std::array`能够改善的地方之一。

### 随堂练习1

把示例中的数组改成：

```cpp
int values[6]{2, 4, 6, 8, 10, 12};
```

在同一个循环里同时计算：

- 元素总和；
- 偶数元素的数量；
- 最大值。

完成后分别输出三个结果。先预测结果，再编译运行。

---

## 二、使用`std::array`保存固定数量数据

`std::array`定义在`<array>`头文件中：

```cpp
std::array<int, 5> values{3, 1, 4, 1, 5};
```

尖括号里的两个部分分别是：

- `int`：元素类型；
- `5`：元素数量。

元素数量是类型的一部分，因此`std::array<int, 5>`和`std::array<int, 8>`是不同类型。

与原生数组相比，`std::array`仍保存固定数量的连续元素，但它提供了常见容器接口：

```cpp
values.size();
values.front();
values.back();
values.at(2);
```

它也支持普通下标：

```cpp
values[2];
```

### `[]`与`at()`

- `values[index]`不进行边界检查；下标错误会导致未定义行为；
- `values.at(index)`会检查边界，越界时通过异常报告错误。

异常将在Day17和Day39逐步学习。今天只需知道：当下标来自外部输入或计算结果时，`at()`可以帮助暴露边界错误；不要为了观察异常而故意在未处理的程序中越界。

### 示例2：固定采样窗口统计

这里使用嵌入式场景是自然的：固定采样窗口的容量在编译时已经确定。

```cpp
#include <array>
#include <iostream>

int main()
{
    std::array<int, 5> samples{1200, 1215, 1190, 1220, 1205};

    int sum{};
    int minimum{samples[0]};
    int maximum{samples[0]};

    for (int sample : samples) {
        sum += sample;

        if (sample < minimum) {
            minimum = sample;
        }

        if (sample > maximum) {
            maximum = sample;
        }
    }

    const double average =
        static_cast<double>(sum) / static_cast<double>(samples.size());

    std::cout << "count = " << samples.size() << '\n';
    std::cout << "min = " << minimum << '\n';
    std::cout << "max = " << maximum << '\n';
    std::cout << "average = " << average << '\n';
    return 0;
}
```

预期输出：

```text
count = 5
min = 1190
max = 1220
average = 1206
```

这里的范围`for`会依次把每个元素的值复制到局部变量`sample`。对于`int`这样的小型类型，按值读取清楚且足够。

`std::array`是一个对象，可以把尺寸一起带入函数类型：

```cpp
void printSamples(const std::array<int, 5>& samples);
```

`const`表示函数只读取数组，引用避免复制整个数组。当前还没有学习模板，因此这个函数只接受恰好5个整数的`std::array`；以后会学习如何让容量成为模板参数。

---

## 三、范围`for`中的值与引用

下面的循环不会修改数组：

```cpp
for (int value : values) {
    value = 0;
}
```

因为`value`只是当前元素的一份副本。

需要修改原元素时，要使用引用：

```cpp
for (int& value : values) {
    value = 0;
}
```

### 示例3：原地修正负数

```cpp
#include <array>
#include <iostream>

int main()
{
    std::array<int, 6> values{4, -2, 7, -1, 0, 5};
    int replaced{};

    for (int& value : values) {
        if (value < 0) {
            value = 0;
            ++replaced;
        }
    }

    std::cout << "replaced = " << replaced << '\n';

    for (int value : values) {
        std::cout << value << ' ';
    }
    std::cout << '\n';
    return 0;
}
```

预期输出：

```text
replaced = 2
4 0 7 0 0 5
```

第一个循环使用`int&`修改数组元素，第二个循环只读取并输出。

### 随堂练习2

下面的程序希望把所有奇数加1，使它们变为偶数，但实际数组没有变化：

```cpp
for (int value : values) {
    if (value % 2 != 0) {
        ++value;
    }
}
```

完成以下任务：

1. 解释为什么没有修改原数组；
2. 做最小修改使程序正确；
3. 再增加一个只读循环，输出修改后的全部元素。

---

## 四、边界与尺寸

处理固定数组时，要始终分清“元素数量”和“最后一个下标”：

```text
元素数量为5
合法下标为0、1、2、3、4
最后一个下标为size() - 1
```

如果只需要遍历所有元素，范围`for`通常比手写下标更不容易出错。如果确实需要下标，循环条件应写成：

```cpp
for (std::size_t index{}; index < values.size(); ++index) {
    // 使用values[index]
}
```

不要写成`index <= values.size()`，因为当`index == values.size()`时已经越界。

`std::array<T, 0>`是合法类型，但它没有首元素，因此不能调用`front()`、`back()`或访问`[0]`。今天的必做代码题都使用非空数组；空容量只作为边界知识了解。

## 重要错误提醒

### 1. 把元素数量当成最后一个下标

```cpp
values[values.size()]; // 越界
```

最后一个合法下标是`values.size() - 1`，前提是数组非空。

### 2. 循环条件写成`<= size()`

```cpp
for (std::size_t i{}; i <= values.size(); ++i) {
    std::cout << values[i] << '\n';
}
```

最后一次循环必然越界，应改成`i < values.size()`。

### 3. 范围`for`按值遍历却期待修改原元素

`for (int value : values)`修改的是副本。需要修改元素时使用`int& value`。

### 4. 认为原生数组参数仍知道元素数量

函数参数`const int values[]`实际上按指针接收，通常需要额外传入长度。`std::array`可以把固定尺寸保留在类型中。

---

## 代码题一：替换负数并统计

在`02_代码题_替换负数`中实现：

```cpp
int replaceNegatives(std::array<int, 6>& values);
```

要求：

- 把所有负数替换为0；
- 返回被替换的元素数量；
- 使用范围`for`和引用修改元素；
- 在`main()`中输出返回值和修改后的数组。

建议至少观察这些情况：

- 同时包含正数、负数和0；
- 没有负数；
- 全部为负数。

<details>
<summary>提示</summary>

循环变量需要写成引用。计数器只在真正替换元素时递增。

</details>

## 代码题二：固定采样窗口统计

在`03_代码题_固定采样窗口统计`中实现一个固定容量采样统计程序。

给定：

```cpp
std::array<int, 8> samples;
```

计算并输出：

- 样本数量；
- 总和；
- 最小值；
- 最大值；
- 平均值。

要求：

- 使用`std::array`和范围`for`；
- 平均值使用`double`计算，避免整数除法；
- 不使用`std::vector`；
- 不调用尚未学习的标准算法；
- 在`main()`中至少运行一组普通数据，并自行增加一组边界数据。

<details>
<summary>提示</summary>

数组容量固定为8，因此可以用第一个元素初始化最小值和最大值。计算平均值前，把总和或尺寸转换为`double`。

</details>

---

## 快速自测

1. `std::array<int, 5>`中的`5`表示什么？
2. 一个包含5个元素的数组，最后一个合法下标是多少？
3. `operator[]`和`at()`在边界检查方面有什么区别？
4. 为什么`for (int value : values)`不能修改数组元素？
5. 原生数组传入普通函数后，为什么经常还要传递长度？

<details>
<summary>参考答案</summary>

1. 数组包含5个`int`元素，且5是类型的一部分。  
2. 4。  
3. `[]`不检查边界；`at()`会检查并通过异常报告越界。  
4. `value`是元素副本；需要修改时应使用`int& value`。  
5. 原生数组参数通常退化为指针，函数本身不再保留原数组尺寸。

</details>

## 巩固与选学

完成必修后，可以选择：

- 把一个使用原生数组和长度参数的小函数改写为固定容量`std::array`版本；
- 分别使用`front()`、`back()`和`at()`读取元素；
- 比较按值范围`for`、按引用范围`for`和按`const`引用范围`for`；
- 了解C++20的`std::span`可以在不拥有数据的情况下接收不同长度的连续区间。今天不要求实现，也不计入完成条件。

## 今日小结

1. 原生数组仍可使用，但传入函数后通常不能自行保留长度；
2. `std::array<T, N>`适合编译期已知容量的固定数据；
3. 范围`for`适合遍历全部元素，使用引用才能修改原元素；
4. `size()`返回元素数量，不是最后一个合法下标；
5. `[]`不检查边界，`at()`会检查边界。

## 算法副线

- 题目：977. Squares of a Sorted Array
- 难度：Easy
- 官方链接：[LeetCode 977](https://leetcode.com/problems/squares-of-a-sorted-array/)
- 建议时间：25分钟
- 训练目标：利用有序数组两端的绝对值关系，用双指针从结果末尾填入平方值
- 三级提示：[algorithms/day-010.md](../algorithms/day-010.md)

LeetCode使用`std::vector`作为题目接口。今天只需认识它的下标、`size()`和按尺寸创建结果数组，不要求系统掌握动态容量。算法是否Accepted不影响Day10正课完成。

## 完成今天的必修部分

当你已经手敲并运行示例、完成两个随堂练习、独立编写两道代码题，并能回答快速自测中的主要问题，就可以继续Day11。巩固、选学和LeetCode按精力单独安排。

下一课将从C字符数组过渡到`std::string`，继续比较“原始数据表示”和“带有常用操作的C++对象”。
