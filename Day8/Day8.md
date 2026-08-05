# Day 8：作用域、存储期与对象生命周期

> 所属阶段：C++基础迁移（Week 2）  
> 日型：概念学习日｜难度：基础  
> C++主线必修：约120分钟｜进阶选学：约20分钟  
> LeetCode：25分钟｜当天总计：约145～165分钟  
> 前置：Day 3悬空引用、Day 7返回路径与边界补练  
> 后续：Day 9将学习`nullptr`以及指针、引用的接口选择  
> 关键词：作用域、名字可见性、存储期、生命周期、自动对象、静态对象、`thread_local`  
> 必做产出：修复5个生命周期错误，并画出对象生存时间线

## 今日学习目标

完成后，你应当能够：

1. 区分“名字在哪里可见”与“对象在什么时候存在”；
2. 判断局部对象进入和离开作用域的时间；
3. 解释自动、静态和线程存储期对象的主要差异；
4. 识别返回局部引用、指针逃逸和遮蔽造成的问题；
5. 为一段短代码画出对象创建、可用和销毁的时间线。

## 今日内容边界

今天必须掌握局部作用域、自动存储期、静态局部对象和悬空访问。`thread_local`今天只要求知道“每个线程各有一份对象”；线程创建与同步到Day 85以后再学。动态存储期只说明它不由普通块作用域直接结束，`new/delete`在Day 29、RAII在Day 30正式学习。今天不要求手写动态内存代码。

## 为什么要学习

C程序员通常知道局部变量离开函数后不能再用，但C++把“对象何时存在”发展成资源管理的基础：对象生命周期结束时，析构函数会运行。以后文件、锁、线程和设备句柄能否可靠释放，都依赖你先看懂作用域和生命周期。

先记住两个不同问题：

- **作用域（scope）**回答名字在源代码的哪些位置可以被找到；
- **生命周期（lifetime）**回答某个对象从何时开始存在，到何时不再存在；
- **存储期（storage duration）**描述承载对象存储空间的最短存续规则。

名字不可见不一定代表对象已经消失；名字仍可见也不保证它引用的对象仍然活着。悬空引用正是第二种情况。

---

## 01：作用域与名字可见性

花括号形成块作用域。内层可以访问外层名字，但内层声明同名变量会遮蔽外层名字。遮蔽通常能编译，却容易让人误判修改的是哪个对象。

### 示例1：块作用域与独立对象

文件：`scope_demo.cpp`

```cpp
#include <iostream>

int main()
{
    int totalSampleCount{10};

    {
        int batchSampleCount{3};
        std::cout << "batch = " << batchSampleCount << '\n';
    }

    std::cout << "total = " << totalSampleCount << '\n';
    return 0;
}
```

预期输出：

```text
batch = 3
total = 10
```

程序进入内层块时创建`batchSampleCount`。离开内层块后，这个对象销毁；外层`totalSampleCount`仍然存在且没有被修改。

课堂练习：把`batchSampleCount`改成与外层相同的`totalSampleCount`，观察高警告等级给出的遮蔽警告；再恢复清晰命名，使项目重新达到零警告。

---

## 02：存储期与生命周期不是同一个词

今天接触四类存储期，但只深入前三类：

| 存储期 | 典型声明 | 大致存在时间 | 今天要求 |
|---|---|---|---|
| 自动 | 普通局部变量 | 每次进入声明所在块时创建，离开时销毁 | 必须掌握 |
| 静态 | 全局变量、`static`局部变量 | 通常贯穿整个程序运行期 | 必须掌握 |
| 线程 | `thread_local`对象 | 每个线程各有一份，随线程存在 | 知道语义 |
| 动态 | 以后使用`new`获得的对象 | 由显式释放或所有者管理 | 延后到Day 29～30 |

对象生命周期通常发生在其存储期之内。基础类型看不出“销毁动作”，但类对象离开生命周期时会调用析构函数，因此今天的规则会直接连接后面的RAII。

C语言类比：C同样有块作用域和静态局部变量；C++更强调“对象”而不只是“一块内存”，因为对象开始和结束生命周期时可能执行构造与析构逻辑。

---

## 03：自动对象与时间线

普通局部对象具有自动存储期。每次函数调用都会产生新的一份局部对象；函数返回或块被正常离开时，该对象生命周期结束。

### 示例2：每次调用都有新的局部对象

文件：`automatic_lifetime.cpp`

```cpp
#include <iostream>

void processSample(int raw)
{
    int calibrated{raw + 1};
    std::cout << calibrated << '\n';
}

int main()
{
    processSample(10);
    processSample(20);
    return 0;
}
```

预期输出：

```text
11
21
```

每次调用都创建独立的`raw`和`calibrated`。第一次调用结束后，它们已经销毁；第二次调用不是继续使用第一次的对象。

时间线可以写成：

```text
进入processSample → raw开始 → calibrated开始 → 输出 → calibrated结束 → raw结束 → 返回
```

课堂练习：在函数内增加一个更小的花括号块和局部变量，把它插入时间线的正确位置。

---

## 04：静态局部对象与`thread_local`

`static`局部对象的名字仍然只有块作用域，但对象只在第一次执行到声明时初始化一次，生命周期持续到程序结束。因此它可以记住两次调用之间的状态。

### 示例3：静态局部计数器

文件：`static_counter.cpp`

```cpp
#include <iostream>

int nextSequence()
{
    static int sequence{};
    ++sequence;
    return sequence;
}

int main()
{
    std::cout << nextSequence() << '\n';
    std::cout << nextSequence() << '\n';
    return 0;
}
```

预期输出：

```text
1
2
```

若去掉`static`，每次调用都会重新创建并零初始化`sequence`，两次都返回1。静态状态并非总是好事：它会让函数依赖历史调用，测试时必须考虑状态是否需要重置。

`thread_local int errorCount{};`表示每个线程各有一份计数器。今天不要创建线程，只需知道它既不是所有线程共享的全局计数器，也不是每次函数调用都重建的普通局部对象。

---

## 05：五类生命周期错误

1. **离开块后继续使用局部对象的地址**：指针仍保存地址，但对象已不存在，解引用是未定义行为。
2. **返回局部变量的引用或指针**：函数返回时局部对象销毁，调用者得到悬空引用或指针。
3. **把遮蔽误当成修改外层对象**：代码可以编译，但实际修改了另一个生命周期更短的对象。
4. **读取未初始化的自动变量**：对象虽然已进入生命周期，但值不确定；基础类型优先使用`{}`初始化。
5. **误以为静态局部变量每次重置**：对象一直存在，历史状态可能污染下一次测试。

一个可靠的分析顺序是：先圈出声明，再标出进入和离开块的位置，然后追踪引用或指针是否越过对象终点。

常见误区：

- “地址数值还在，所以对象还在”——错误；存储位置可被保留或复用，不代表对象生命周期仍有效。
- “能编译就没有悬空”——错误；很多生命周期错误属于运行期未定义行为。
- “`static`让变量全局可见”——错误；静态局部变量的名字仍只在函数块内可见。
- “`thread_local`等于普通全局变量”——错误；它为每个线程提供独立对象。

---

## 代码题一：修复五个生命周期错误

- 类型：错误修复｜难度：基础
- 要求：在`06_代码题_修复五个生命周期错误`中自行编写并修复5个短案例，分别覆盖：返回局部引用、局部地址逃逸、变量遮蔽、未初始化读取、静态状态误判。
- 输出：每个案例打印修复后的可验证结果，并在注释中写出“对象开始—对象结束—原代码为何错误”。
- 限制：不使用动态内存、类、异常或智能指针。
- 完成标准：C++17高警告等级编译通过；5个案例均有原因、最小修正和时间线。

建议测试：

1. 连续调用修复后的函数两次，确认没有引用已销毁对象；
2. 内层块结束后确认外层值符合预期；
3. 自动变量在所有读取路径前都已初始化；
4. 静态计数器连续调用得到`1, 2, 3`；
5. 普通局部计数器连续调用始终从初值开始。

<details>
<summary>提示</summary>

返回多个结果时先用非`const`引用输出；需要跨函数使用的值由调用者创建并传入。遮蔽案例可以通过改名或去掉重复类型声明修正。

</details>

---

## 代码题二：设备采样统计器

- 类型：独立实现｜难度：基础
- 要求：实现`bool recordSample(int sample, int& latest, int& callCount)`。合法范围为`0～4095`；失败时不修改两个输出。另写`int nextPacketSequence()`，使用静态局部变量返回从1开始递增的序号。
- 输入：在`main()`中准备固定测试数据，不要求交互输入。
- 输出：打印每次调用是否成功、最新采样值、成功次数和报文序号。
- 限制：验证成功后再修改输出；不使用全局变量、动态内存和类。
- 完成标准：能解释`latest/callCount`由调用者管理，而序号对象为什么能跨调用保留。

建议测试：

1. `sample=0`成功；
2. `sample=4095`成功；
3. `sample=-1`失败且两个输出不变；
4. `sample=4096`失败且两个输出不变；
5. 连续三次调用`nextPacketSequence()`得到`1,2,3`。

<details>
<summary>提示</summary>

先把旧输出保存为测试哨兵值。`recordSample`先完成全部验证，最后再依次赋值；静态序号只放在`nextPacketSequence`内部。

</details>

---

## 自测题

1. 作用域和生命周期分别回答什么问题？
2. 内层同名变量会修改外层对象吗？
3. 普通局部变量为什么不能通过引用安全地返回？
4. 静态局部变量的名字和对象分别存在多久？
5. `thread_local`对象是一份还是每个线程一份？
6. 动态对象和RAII今天是否计入完成要求？

<details>
<summary>查看答案与解析</summary>

1. 作用域决定名字可见范围，生命周期决定对象存在时间。  
2. 不会；内层声明创建另一个对象并遮蔽外层名字。  
3. 函数返回后局部对象生命周期结束，引用会悬空。  
4. 名字只在声明块内可见，对象从首次初始化持续到程序结束。  
5. 每个线程各有一份。  
6. 不计入；动态存储期在Day 29、RAII在Day 30正式学习。

</details>

---

## LeetCode 704：Binary Search

- 难度：Easy
- 主题：有序数组、二分查找
- 官方链接：[LeetCode 704](https://leetcode.com/problems/binary-search/)
- 建议独立尝试：25分钟
- 训练目标：维护闭区间边界，并避免遗漏单元素区间

题意摘要：在一个升序整数数组中查找目标值，找到就返回下标，否则返回`-1`。

### 最小语法桥接

`std::vector<int>& nums`引用题目给出的数组；`nums[index]`按下标访问元素。`nums.size()`返回无符号大小，为避免空数组时先减1造成下溢，可先转换整体大小：

```cpp
int right = static_cast<int>(nums.size()) - 1;
```

<details>
<summary>提示1</summary>

数组已经有序。比较中间值与目标后，可以排除一半不可能的位置。

</details>

<details>
<summary>提示2</summary>

维护仍可能包含答案的闭区间`[left, right]`。循环条件应允许`left == right`。

</details>

<details>
<summary>提示3</summary>

计算`middle = left + (right - left) / 2`。中间值偏小时令`left = middle + 1`，偏大时令`right = middle - 1`。

</details>

<details>
<summary>查看完整解题思路与C++17参考实现</summary>

最直接的方法是从头到尾比较，时间复杂度为`O(n)`。由于输入保证升序，可以根据中间值与目标的大小关系，每轮排除一半区间。

闭区间不变量：循环开始时，如果目标存在，它一定在`[left, right]`内。中间值偏小意味着`middle`及其左侧都不是答案；偏大时同理排除右侧。

步骤：

1. 初始化`left=0`、`right=size-1`；
2. 当`left<=right`时计算中间位置；
3. 相等立即返回；否则缩小到不可能包含当前中点的半区；
4. 区间为空时返回`-1`。

```cpp
#include <vector>

class Solution {
public:
    int search(std::vector<int>& nums, int target)
    {
        int left{};
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            const int middle = left + (right - left) / 2;

            if (nums[middle] == target) {
                return middle;
            }

            if (nums[middle] < target) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        return -1;
    }
};
```

时间复杂度：`O(log n)`；额外空间复杂度：`O(1)`。

关键点：使用`left <= right`才能检查最后一个候选位置；`+1/-1`确保区间严格缩小；整体转换`size()`后再减1可让空数组得到`right=-1`。

边界与常见错误：空数组、单元素数组、目标位于两端、目标不存在；不要写成`left < right`后忘记检查最后位置，也不要更新成`left=middle`造成死循环。

自定义测试：

```text
[-1,0,3,5,9,12], target=9  -> 4
[-1,0,3,5,9,12], target=2  -> -1
[5], target=5               -> 0
[5], target=-5              -> -1
[], target=1                -> -1
```

可选方案：线性扫描对无序数组也适用，但没有利用升序条件；递归二分会增加调用栈，当前迭代写法更直接。迁移练习：LeetCode 35 Search Insert Position。

</details>

---

## 编译与验收

MSVC：

```text
cl /std:c++17 /W4 /permissive- /EHsc /utf-8 main.cpp
```

GCC/Clang：

```text
g++ main.cpp -std=c++17 -Wall -Wextra -pedantic -o app
```

验证时记录：5个错误的根因与修正、两道代码题的测试结果、LeetCode独立尝试用时和复杂度。

## 今日总结与完成标准

- 能区分作用域、存储期和生命周期；
- 已修复并解释5个生命周期错误，画出至少一条完整时间线；
- 两道代码题通过给定边界测试；
- 能解释自动局部对象与静态局部对象的差异；
- LeetCode 704已独立尝试，并记录`O(log n)`时间、`O(1)`空间；
- 全部代码以C++17高警告等级编译，无未解释警告；
- 写3～5句复盘，记录一次悬空风险和一次边界错误。

## 主要参考资料

- [cppreference：Scope](https://en.cppreference.com/w/cpp/language/scope.html)
- [cppreference：Storage duration](https://en.cppreference.com/w/cpp/language/storage_duration.html)
- [cppreference：Object lifetime](https://en.cppreference.com/w/cpp/language/lifetime.html)
- [LeetCode 704](https://leetcode.com/problems/binary-search/)

下一课Day 9：在生命周期基础上判断什么时候用指针、引用或`nullptr`表达“对象可能不存在”。
