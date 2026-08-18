# Day 21 阶段测评记录

## 无提示知识地图

### 1. 类型与初始化

- `{}`初始化解决什么问题？ 解决初始化和赋值含义不清
- `auto`适合什么场景，什么时候会让类型意图不清楚？ auto适合用来简化复杂类型的重复书写
- 为什么不能依赖未初始化局部变量？ 未初始化的局部变量值是不确定的，访问会造成未定义行为
- `enum class`相比普通整数常量提供了什么约束？ enum class 在调用时必须携带类型

### 2. 引用、指针与生命周期

- 引用参数与指针参数分别怎样表达“必须存在”和“允许为空”？ 
- `const T&`限制了谁？ 限制接收引用的对象，防止通过对象修改引用指向的本身
- 为什么不能返回局部对象的引用？ 因为局部对象在作用域结束时就会销毁，会造成悬空引用
- `std::string_view`不拥有什么？它最常见的风险是什么？ 不拥有字符串对象本身  返回局部字符串的string_view
  
3. 函数与接口

- 重载由哪些信息区分？返回类型能否单独区分重载？ 重载由参数类型，数量来区分。单返回值不能区分函数重载
- 默认参数为什么可能与重载产生歧义？ 默认参数和重载函数可能造成调用时语义不清，编译器无法确定调用那个函数
- `constexpr`函数的基础作用是什么？  让函数可以在编译阶段确定值，也可以在运行时调用
- 失败时为什么通常应该先验证，再修改输出或对象？ 因为先输出或先修改 再验证 即使验证不通过修改也已经发生

### 4. 类与对象

- `struct`与`class`默认访问权限有什么区别？ struct 默认权限public  class默认权限private
- 构造函数和成员初始化列表分别负责什么？  构造函数负责对象创建时提供初始化的方式  初始化列表负责对具体成员进行初始化
- 成员实际初始化顺序由什么决定？  有成员的声明顺序决定
- 普通`std::string`成员是否需要手写析构函数？  不需要
- 什么是类不变量？  只能通过特定函数修改的量

### 5. 多文件与错误处理

- 声明与定义分别解决什么问题？  声明是告诉编译器有该对象  定义是具体实现
- include guard解决哪个范围的重复包含？ 头文件中互相包含
- 编译错误与链接错误怎样初步区分？  看报错的类型
- 命名空间和匿名命名空间各自解决什么问题？  命名空间可以跨文件使用，解决名称冲突问题   匿名命名空间提供仅供当前文件使用的对象或函数
- `bool`、错误码和结果结构体的表达能力有什么差异？  bool只可以表示程序运行正确或错误   错误码可以返回具体错误类型  结果结构体返回具体错误类型和信息

## 代码阅读与修复

### 题1

const std::string& buildMessage()
{
    std::string message{"ready"};
    return message;
}
- 现象：报错
- 根因：返回局部对象的引用
- 最小修复：将返回值的引用符号去掉

### 题2
// rate.h
bool setRate(int rate);

cpp
```cpp
// rate.cpp
int setRate(int rate)
{
    return rate;
}
```
回答：

1. 这是不是同一个函数的声明与定义？  不是
2. 错误更可能出现在哪个阶段？  编译阶段
3. 如果接口语义是“设置成功或失败”，应保留哪种返回类型？ 保持bool类型

### 题3

class Packet {
public:
    explicit Packet(int payloadSize)
        : totalSize_{payloadSize_ + 4}, payloadSize_{payloadSize}
    {
    }

private:
    int totalSize_;
    int payloadSize_;
};
cpp回答：

1. 哪个成员最先初始化？totalSize_先初始化
2. `totalSize_`读取了什么？ 读取了未初始化的变量payloadSize_
3. 怎样调整声明或直接使用构造参数，使依赖关系明确？ 先声明payloadSize_ 再声明totalSize_
### 题4

bool setName(std::string_view text, std::string& name)
{
    name = text;
    if (text.empty() || text.size() > 16) {
        return false;
    }
    return true;
}
bool setName(std::string_view text, std::string& name)
{
    if (text.empty() || text.size() > 16) {
        return false;
    }
        name = text;
    return true;
}
回答：失败后`name`是否保持原值？请改成“验证全部成功后再提交修改”。不能保持原值
## 独立实现测试

- 输入：
- 预期：
- 实际：

按需复制以上三行，记录正常、边界、非法输入和失败后状态检查。

## 复盘

待完成。
