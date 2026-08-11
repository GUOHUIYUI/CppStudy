# Day 14：Week 2项目——命令行设备配置器 v2

> 所属阶段：C++基础迁移（Week 2）
> 日型：项目日
> 必修：约160～180分钟
> 巩固与选学：约20～40分钟
> LeetCode：25分钟，单独计算

今天不再集中引入新语法，而是把Day 8～13的知识组合起来，完成一个可以交互、能拒绝非法输入、能显示当前状态的小程序。

## 项目目标

完成后，你应该能够：

1. 用`std::string`接收和拆分命令；
2. 用`enum class`表示设备状态和命令结果；
3. 用`std::array`保存固定数量的采样值；
4. 用类保护名称、采样率等配置规则；
5. 通过一组输入输出证明成功与失败路径符合预期。

## 今天不做什么

- 不拆分`.h/.cpp`，多文件工程从Day15开始；
- 不使用动态内存、智能指针或异常；
- 不实现真实串口通信；
- 不追求通用命令框架或企业级配置系统；
- 不保存悬空的`std::string_view`。

## 一、程序行为

程序循环读取一整行，支持以下命令：

```text
SHOW
NAME <新名称>
RATE <1到1000>
STATE OFFLINE
STATE IDLE
STATE RUNNING
SAMPLES
QUIT
```

初始配置建议为：

```text
name=device
rate=100
state=OFFLINE
```

`SAMPLES`输出固定的8个采样值以及数量、最小值、最大值和平均值。今天不要求从用户输入采样数据。

## 二、推荐的数据类型

```cpp
enum class DeviceState {
    offline,
    idle,
    running
};

enum class CommandResult {
    ok,
    emptyInput,
    unknownCommand,
    missingArgument,
    invalidArgument
};
```

`DeviceConfig`至少维护名称、采样率和状态。成员变量应为`private`，通过成员函数修改：

```cpp
class DeviceConfig {
public:
    bool setName(std::string_view name);
    bool setRate(int rate);
    void setState(DeviceState state);

    const std::string& name() const;
    int rate() const;
    DeviceState state() const;

private:
    std::string name_{"device"};
    int rate_{100};
    DeviceState state_{DeviceState::offline};
};
```

这是任务接口建议，不是完整答案。你可以调整函数名，但应保持相同规则。

## 三、解析顺序

建议把每一行分成“命令名”和“其余参数”：

1. 检查空输入；
2. 使用`find(' ')`找到第一个空格；
3. 没有空格时整行作为命令名；
4. 有空格时拆出命令名和参数；
5. 根据命令名调用相应操作；
6. 只有验证成功才修改配置。

数字转换实现一个小辅助函数：

```cpp
bool parseRate(std::string_view text, int& rate);
```

先拒绝空串，再逐个确认字符位于`'0'`到`'9'`，按`value = value * 10 + digit`累积；一旦数值超过1000即可失败。最后检查1～1000，并且只在成功时写入`rate`。这样`"100abc"`不会被当成合法100，也不需要提前学习异常。

## 四、固定采样统计

使用：

```cpp
const std::array<int, 8> samples{120, 118, 121, 125, 119, 123, 122, 120};
```

用范围`for`计算总和、最小值和最大值，平均值使用`double`。数组固定非空，因此可以用首元素初始化最小值和最大值。

## 五、分步实现建议

### 第一步：配置对象

先完成`DeviceConfig`并直接调用成员函数测试，不接入命令解析。确认非法名称和非法采样率不会改变旧值。

### 第二步：状态转换

实现状态到文本、文本到状态两个方向。未知状态文本必须失败，不能默认为某个合法状态。

### 第三步：单行命令

实现处理一行输入的函数。它返回`CommandResult`，输出统一由调用者完成，避免解析函数到处打印。

### 第四步：交互循环

使用`std::getline`循环读取。遇到`QUIT`正常结束；输入流结束也应退出，不能形成死循环。

### 第五步：保存测试证据

把手工测试输入和观察到的输出分别写入项目内的`test-input.txt`和`test-output.txt`。这两个文件是项目结果的一部分，不需要自动测试框架。

## 必测场景

建议至少覆盖这些行为，不要求使用固定打印格式：

1. `SHOW`显示初始值；
2. 合法修改名称和采样率后再次`SHOW`；
3. 空名称、17字符名称、采样率0和1001被拒绝且旧值不变；
4. 三种合法状态都可设置；
5. 未知状态和未知命令返回清楚错误；
6. `SAMPLES`统计值正确；
7. 空行不会崩溃；
8. `QUIT`和输入结束都能退出。

## 重要错误提醒

1. 不要让解析得到的`string_view`在原输入行改变后继续保存；
2. 不要先写入成员变量再判断参数是否合法；
3. `switch`或状态转换不能漏掉合法枚举值；
4. `getline`失败后应结束循环，不能反复处理旧输入。

## 项目完成标准

你能完成以下内容，就可以进入Week 3：

- 程序在C++17高警告等级下编译；
- 支持本课列出的命令；
- 非法命令不会破坏已有配置；
- 固定采样统计结果正确；
- 保存一份测试输入与输出；
- 写5～8句简短设计说明，解释字符串所有权、枚举用途和类维护的规则。

## 快速复盘

1. 哪些文本由`std::string`拥有，哪些`string_view`只在函数调用期间借用？
   局部string的`string_view只在函数调用期间借用
2. 为什么状态不使用0、1、2魔法整数？
   因为使用魔法整数意义不明确
3. 哪些字段必须由类的成员函数保护？
   私有的，不能随便修改的字段
4. 为什么固定8个采样值适合`std::array`？
   因为已知数组长度
5. 项目中哪条失败路径最容易意外修改旧值？

## 本周小结

1. 生命周期决定指针、引用和视图能否安全使用；
2. `std::array`保存固定数量数据，`std::string`拥有可变文本；
3. `enum class`表达有限状态，减少不同类别混用；
4. 类把数据与维护数据规则的操作放在一起；
5. 综合程序要通过真实输入输出验证成功和失败路径。

## 算法副线

- 题目：383. Ransom Note
- 难度：Easy
- 官方链接：[LeetCode 383](https://leetcode.com/problems/ransom-note/)
- 建议时间：25分钟
- 训练目标：使用固定计数表统计字符需求与供给
- 三级提示：[algorithms/day-014.md](../algorithms/day-014.md)

Day15将正式学习头文件、源文件、声明与定义，把当前单文件项目拆成多文件工程。
