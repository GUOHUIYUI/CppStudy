# device-config-cli

## 项目用途

一个命令行设备配置器：通过标准输入逐行读取命令，修改设备的名称、采样率与运行状态，并可用 `SHOW` 查看当前配置。用于练习 C++ 的头文件/源文件划分、命名空间、强类型枚举，以及"状态 + 字段 + 原因"的错误结果返回方式。

## 构建方法

1. 使用 Visual Studio 2022 打开解决方案 `Day20.slnx`；
2. 选择 `Debug` + `x64` 配置；
3. 生成解决方案（`Ctrl+Shift+B`）；
4. 生成的程序位于 `x64\Debug\device-config-cli.exe`，在终端中直接运行并输入命令。

## 支持的命令

| 命令 | 说明 |
|---|---|
| `NAME <text>` | 设置设备名称，长度 1～16 |
| `RATE <integer>` | 设置采样率，范围 1～1000 |
| `STATE <value>` | 设置状态，取值 `kOff` / `kOn` / `kUnknown` |
| `SHOW` | 显示当前配置（名称、采样率、状态） |
| `QUIT` | 退出程序 |

## 输入规则与参数范围

- 命令一律大写；命令与参数之间至少一个空格；
- 参数首尾的多余空格会被忽略（如 `RATE  500` 等价于 `RATE 500`）；
- 名称暂不支持包含空格；
- 空输入、未知命令、缺少参数、非法参数会以 `error: <原因> (<字段>)` 的形式报告，修改失败时原配置保持不变；
- 输入流结束（EOF，如 `Ctrl+Z` 回车）与 `QUIT` 都能结束程序。

## 示例会话

```
> SHOW
name: device
rate: 100
state: kOff
> NAME myDevice
> RATE 500
> SHOW
name: myDevice
rate: 500
state: kOff
> RATE 0
error: rate invalid (rate)
> STATE bad
error: state must be kOff/kOn/kUnknown (state)
> BADCMD
error: unknown command (command)
> QUIT
```

## 当前限制

- 名称不支持包含空格；
- 命令大小写敏感，只接受大写；
- 状态只有 `kOff` / `kOn` / `kUnknown` 三种固定取值，与任务书草案中的 `OFFLINE/IDLE/RUNNING` 不一致（待统一）；
- 配置不持久化，程序退出后恢复初始值；
- `QUIT` 不接受参数（`QUIT` 后不能跟空格）。
