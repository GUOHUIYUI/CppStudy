# Day 9：`nullptr`与安全的指针/引用接口

> 所属阶段：C++基础迁移（Week 2）  
> 日型：概念学习日｜难度：基础  
> C++主线必修：约120分钟｜进阶选学：约20分钟  
> LeetCode：25分钟｜当天总计：约145～165分钟  
> 前置：C指针、Day 4 `const`、Day 8生命周期  
> 后续：Day 10学习原生数组、`std::array`和范围`for`  
> 关键词：指针、引用、`nullptr`、可选对象、只读访问、非拥有指针  
> 必做产出：重构可选设备句柄接口，消除`NULL`与魔法值

## 今日学习目标

完成后，你应当能够：

1. 使用`nullptr`初始化、判断和清空指针；
2. 用引用表达“对象必须存在”，用指针表达“对象可以不存在”；
3. 区分`const T*`、`T*`以及引用输出参数的接口承诺；
4. 识别空指针解引用、悬空指针和错误所有权假设；
5. 将使用`NULL`或`-1`表示无效设备的接口重构为明确的可选指针接口。

## 今日内容边界

今天必须掌握`nullptr`、空指针检查，以及指针/引用的接口选择。裸指针今天只表示“观察或访问某个现有对象”，不表示负责释放对象。动态内存到Day 29、RAII到Day 30、智能指针到Day 34学习；今天禁止使用`new/delete`和智能指针。

## 为什么C++还需要指针

引用适合表达“调用期间一定有一个有效对象”，但它不能自然表示“没有对象”。设备可能离线、句柄可能尚未建立、查找可能失败，这些场景需要一种明确的可选状态。裸指针可以指向对象，也可以等于`nullptr`，因此适合表达非拥有的可选访问。

选择接口前先回答：

- 参数能否缺省？不能缺省时优先引用；能够缺省时使用可判空指针。
- 函数是否允许修改对象？只读对象使用`const T*`或`const T&`。
- 函数是否取得所有权？今天所有裸指针都不取得所有权，调用者必须保证对象活着。

---

## 01：指针与`nullptr`

`nullptr`是C++专门的空指针字面量。它不会像整数`0`或某些实现中的`NULL`那样被误认为普通整数重载。

### 示例1：`nullptr`选择指针重载

文件：`nullptr_overload.cpp`

```cpp
#include <iostream>

void report(int errorCode)
{
    std::cout << "error = " << errorCode << '\n';
}

void report(const int* value)
{
    std::cout << (value == nullptr ? "no value" : "has value") << '\n';
}

int main()
{
    report(0);
    report(nullptr);
    return 0;
}
```

预期输出：

```text
error = 0
no value
```

`0`精确匹配整数版本，`nullptr`匹配指针版本，调用意图清楚。工程代码中不要再用`NULL`或魔法整数表示空指针。

课堂练习：声明`int* reading{nullptr};`，先判空，再让它指向一个局部`int`并输出该值。

---

## 02：指针和引用表达不同接口语义

如果设备必须存在，可以使用引用：

```cpp
void resetDevice(DeviceHandle& device);
```

如果设备允许不存在，可以使用指针：

```cpp
bool readDevice(const DeviceHandle* device, int& output);
```

第二个接口中，`device`是可选的只读输入；`output`是必须存在的输出对象。函数应先检查`device == nullptr`，失败时返回`false`且不修改`output`。

### 示例2：可选输入与必需输出

文件：`optional_device.cpp`

```cpp
#include <iostream>

struct DeviceHandle {
    int id;
};

bool readDevice(const DeviceHandle* device, int& output)
{
    if (device == nullptr) {
        return false;
    }

    output = device->id * 10;
    return true;
}

int main()
{
    DeviceHandle sensor{7};
    int reading{-1};

    std::cout << readDevice(&sensor, reading) << ' ' << reading << '\n';
    std::cout << readDevice(nullptr, reading) << ' ' << reading << '\n';
    return 0;
}
```

预期输出：

```text
1 70
0 70
```

第一次传入对象地址并成功更新结果；第二次明确表示设备不存在，函数返回失败且保留原结果。`&sensor`取得地址，`device->id`通过指针访问成员。

课堂练习：给`sensor.id`增加合法范围`0～255`；非法时同样不得修改`output`。

---

## 03：`const`放在指针附近时约束谁

- `const DeviceHandle* device`：可以改变指针让它指向别处，但不能通过它修改设备；常用于只读输入。
- `DeviceHandle* device`：可以通过指针修改设备；仍然必须先判空。
- `DeviceHandle* const device`：指针这个局部副本不能改指向，但可以修改设备。它较少用于公开函数声明，今天只需会读。
- `const DeviceHandle& device`：设备必须存在，并且函数只读。

### 示例3：必需的可写引用

文件：`required_reference.cpp`

```cpp
#include <iostream>

struct DeviceHandle {
    int id;
    bool online;
};

void markOffline(DeviceHandle& device)
{
    device.online = false;
}

int main()
{
    DeviceHandle device{3, true};
    markOffline(device);
    std::cout << device.online << '\n';
    return 0;
}
```

预期输出：

```text
0
```

这里调用者必须提供真实设备对象，非`const`引用明确表示函数会修改它。若“没有设备”是合法状态，就不应伪造`id=-1`对象，而应把接口改成可空指针。

---

## 04：重构可选设备句柄

不推荐的旧接口：

```cpp
int readDevice(int handleId); // -1究竟是无设备、读取失败，还是合法值？
```

推荐拆开对象是否存在、操作是否成功和输出结果：

```cpp
bool readDevice(const DeviceHandle* device, int& output);
```

接口使用者从类型上就能看出：设备可能为空；函数只读设备；结果对象必须存在；返回值表示本次读取成功与否。错误原因以后可以用枚举或更丰富的错误类型表达，今天不引入新主题。

---

## 05：空指针、悬空指针与所有权边界

1. **未判空就解引用**：`pointer->member`要求指针确实指向存活对象；空指针解引用是未定义行为。
2. **返回局部对象地址**：函数返回后对象已销毁，得到的是悬空指针；改为返回值或让调用者提供输出对象。
3. **误以为裸指针拥有对象**：今天的接口只借用对象，不能对传入指针执行`delete`。
4. **用`NULL`调用重载函数**：它可能被当成整数；使用`nullptr`表达空指针意图。
5. **成功前修改输出参数**：先验证指针和业务规则，最后再写输出。

指针非空也不代表安全：它还可能悬空。调用者必须保证被指向对象的生命周期覆盖整次函数调用。

---

## 代码题一：重构可选设备句柄接口

- 类型：接口重构｜难度：基础
- 已知条件：旧代码用`handleId == -1`表示设备不存在。
- 要求：定义仅含`int id`和`bool online`的`DeviceHandle`；实现`bool queryDevice(const DeviceHandle* device, int& status)`。
- 输入：`device`允许为`nullptr`；设备必须在线，且`id`处于`0～255`。
- 输出：成功时把`id * 10`写入`status`并返回`true`；失败时返回`false`且保持`status`原值。
- 限制：不使用`NULL`、魔法无效句柄、动态内存、异常或智能指针。
- 完成标准：能解释为什么设备用指针、结果用引用。

建议测试：

1. `nullptr`失败，哨兵值保持不变；
2. 在线设备`id=0`成功；
3. 在线设备`id=255`成功；
4. 离线设备失败；
5. `id=-1`或`256`失败。

<details>
<summary>提示</summary>

判断顺序为：先判空，再检查`online`和`id`，最后一次性写入`status`。不要在打印函数中隐藏业务判断。

</details>

---

## 代码题二：主备设备选择器

- 类型：独立实现｜难度：基础
- 要求：实现`const DeviceHandle* selectDevice(bool primaryOnline, bool backupOnline, const DeviceHandle& primary, const DeviceHandle& backup)`。
- 输出规则：主设备在线时返回其地址；否则备用在线时返回备用地址；都离线时返回`nullptr`。
- 验证：调用选择器后必须先判空，再读取所选设备；不得返回函数内部局部对象地址。
- 限制：返回的指针只借用调用者对象，不负责销毁。
- 完成标准：能画出两个设备对象与返回指针的生命周期关系。

建议测试：

1. 主、备都在线时选择主设备；
2. 仅主设备在线；
3. 仅备用设备在线；
4. 两者都离线时返回`nullptr`；
5. 选择后确认原设备对象未被修改。

<details>
<summary>提示</summary>

参数引用保证两个候选对象都存在；返回`&primary`或`&backup`不会复制对象。两者均不可用时才返回`nullptr`。

</details>

---

## 自测题

1. `nullptr`比`NULL`更适合C++接口的原因是什么？
2. 参数一定存在且允许修改时，应优先使用哪种类型？
3. 参数可能不存在且只读时，应使用哪种类型？
4. 指针不等于`nullptr`是否足以证明可以安全解引用？
5. `const DeviceHandle*`中的`const`约束谁？
6. 今天的裸指针是否拥有对象、是否可以`delete`？

<details>
<summary>查看答案与解析</summary>

1. `nullptr`具有专门的空指针类型，不会表达普通整数0。  
2. 非`const`引用，如`DeviceHandle&`。  
3. 指向只读对象的指针，如`const DeviceHandle*`。  
4. 不足；指针还可能指向生命周期已经结束的对象。  
5. 约束被指向对象，不能通过该指针修改设备。  
6. 不拥有，也不能释放；今天只表示借用访问。

</details>

---

## LeetCode 35：Search Insert Position

- 难度：Easy
- 主题：二分查找、插入边界
- 官方链接：[LeetCode 35](https://leetcode.com/problems/search-insert-position/)
- 建议独立尝试：25分钟
- 训练目标：在闭区间二分结束后理解`left`为什么就是插入位置

题意摘要：给定严格递增的整数数组和目标值，找到目标就返回下标；不存在时返回保持有序所需的插入位置。

### Day 8边界回练

闭区间`[left, right]`中，中间值小于目标时必须执行`left = middle + 1`，因为`middle`及其左边都不可能是答案。写成`middle - 1`会让左边界倒退，导致死循环或错误访问。

<details>
<summary>提示1</summary>

先使用与Binary Search相同的闭区间。目标存在时直接返回。

</details>

<details>
<summary>提示2</summary>

目标更大时移动`left`，目标更小时移动`right`。循环结束意味着候选区间已经为空。

</details>

<details>
<summary>提示3</summary>

循环退出时，`left`左边的元素都小于目标，`left`位置开始的元素都不小于目标，因此返回`left`。

</details>

<details>
<summary>查看完整解题思路与C++17参考实现</summary>

线性扫描第一个不小于目标的位置需要`O(n)`时间。有序数组允许每轮排除一半范围。维护闭区间不变量：若目标存在，它在`[left,right]`内；同时`left`最终会停在第一个可以放置目标的位置。

步骤：初始化左右边界；循环中比较中间值；相等直接返回；偏小移动左边界到`middle+1`，偏大移动右边界到`middle-1`；区间为空后返回`left`。

```cpp
#include <vector>

class Solution {
public:
    int searchInsert(std::vector<int>& nums, int target)
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

        return left;
    }
};
```

时间复杂度：`O(log n)`；额外空间复杂度：`O(1)`。

关键点：`left <= right`会检查最后一个候选；边界每轮越过`middle`，保证区间缩小；空数组时`right=-1`，循环不执行并返回0。

边界与常见错误：目标小于所有值时返回0；大于所有值时返回数组长度；单元素数组要分别测小于、等于、大于；不要把`left = middle + 1`误写成减1。

自定义测试：

```text
[1,3,5,6], target=5 -> 2
[1,3,5,6], target=2 -> 1
[1,3,5,6], target=7 -> 4
[1,3,5,6], target=0 -> 0
[1], target=1       -> 0
```

可选方案：使用左闭右开区间`[left,right)`也能实现，但更新规则必须整套一致。迁移练习：LeetCode 704 Binary Search，修正Day 8版本后重新运行边界测试。

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

## 今日总结与完成标准

- 所有空指针都使用`nullptr`表示，并在解引用前检查；
- 能根据“必须存在/可以不存在”和“只读/可写”选择指针或引用；
- 两道代码题通过给定测试，失败路径不修改输出；
- 能解释今天的裸指针只是借用，不负责释放对象；
- LeetCode 35独立尝试完成，并修正Day 8二分边界错误；
- 全部代码以C++17高警告等级编译，无未解释警告；
- 写3～5句复盘，记录一次接口选择和一次二分边界判断。

## 主要参考资料

- [cppreference：Pointer declaration](https://en.cppreference.com/w/cpp/language/pointer.html)
- [cppreference：`nullptr`](https://en.cppreference.com/w/cpp/language/nullptr.html)
- [cppreference：Reference declaration](https://en.cppreference.com/w/cpp/language/reference.html)
- [LeetCode 35](https://leetcode.com/problems/search-insert-position/)

下一课Day 10：使用原生数组和`std::array`组织固定数量数据，并系统处理尺寸与边界。
