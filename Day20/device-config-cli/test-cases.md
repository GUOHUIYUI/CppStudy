# device-config-cli 测试记录

## 测试环境

- 构建：Debug x64（VS 2022，C++17，警告等级 4）
- 初始配置：`rate=100`，`name=device`，`state=kOff`
- 输入方式：标准输入逐行读取，`>` 为程序提示符
- 日期：2026-08-18

## 初始状态与正常流程

### 1. 程序启动后 SHOW

- 输入：`SHOW`
- 预期：显示 name: device / rate: 100 / state: kOff
- 实际：
  ```
  > SHOW
  name: device
  rate: 100
  state: kOff
  ```
- 是否通过：是

### 2. 合法名称修改

- 输入：`NAME myDevice`
- 预期：成功，无输出
- 实际：成功，无输出
- 是否通过：是

### 3. 合法最短采样率

- 输入：`RATE 1`
- 预期：成功，无输出
- 实际：成功，无输出
- 是否通过：是

### 4. 合法最大采样率

- 输入：`RATE 1000`
- 预期：成功，无输出
- 实际：成功，无输出
- 是否通过：是

### 5. 普通采样率修改

- 输入：`RATE 500`
- 预期：成功，无输出
- 实际：成功，无输出
- 是否通过：是

### 6. 三种合法状态

- 输入：`STATE kOn`、`STATE kOff`、`STATE kUnknown`
- 预期：均成功，无输出
- 实际：均成功，无输出
- 是否通过：是

### 7. 参数首尾多余空格

- 输入：`RATE  500`（命令与参数之间两个空格）
- 预期：成功，等价于 `RATE 500`
- 实际：成功，后续 `SHOW` 显示 rate: 500
- 是否通过：是

### 8. 多次修改后 SHOW

- 输入：`NAME myDevice`、`RATE 500`、`SHOW`
- 预期：显示 name: myDevice / rate: 500 / state: kOff
- 实际：
  ```
  > SHOW
  name: myDevice
  rate: 500
  state: kOff
  ```
- 是否通过：是

## 失败与边界

### 9. 空行

- 输入：（空行）
- 预期：`error: empty input (command)`
- 实际：`> error: empty input (command)`
- 是否通过：是

### 10. 未知命令

- 输入：`BADCMD`
- 预期：`error: unknown command (command)`
- 实际：`> error: unknown command (command)`
- 是否通过：是

### 11. NAME 缺少参数

- 输入：`NAME`
- 预期：`error: name argument missing (name)`
- 实际：`> error: name argument missing (name)`
- 是否通过：是

### 12. 名称超过 16 字符

- 输入：`NAME abcdefghijklmnopq`（17 字符）
- 预期：`error: name invalid (name)`，名称保持不变
- 实际：`> error: name invalid (name)`，后续 `SHOW` 显示 name: device
- 是否通过：是

### 13. RATE 缺少参数

- 输入：`RATE`
- 预期：`error: rate argument missing (rate)`
- 实际：`> error: rate argument missing (rate)`
- 是否通过：是

### 14. RATE 低于下界

- 输入：`RATE 0`
- 预期：`error: rate invalid (rate)`
- 实际：`> error: rate invalid (rate)`
- 是否通过：是

### 15. RATE 超过上界

- 输入：`RATE 1001`
- 预期：`error: rate invalid (rate)`，采样率保持不变
- 实际：`> error: rate invalid (rate)`，后续 `SHOW` 显示 rate 为最后一次合法值 1000
- 是否通过：是

### 16. RATE 非数字

- 输入：`RATE abc`
- 预期：`error: rate must be an integer (rate)`，不崩溃
- 实际：`> error: rate must be an integer (rate)`
- 是否通过：是

### 17. 非法状态值

- 输入：`STATE bad`
- 预期：`error: state must be kOff/kOn/kUnknown (state)`
- 实际：`> error: state must be kOff/kOn/kUnknown (state)`
- 是否通过：是

### 18. 失败后原配置保持

- 输入：`RATE 0`、`RATE abc`、`RATE 1001` 后接 `SHOW`
- 预期：采样率保持最后一次合法值不变
- 实际：`SHOW` 显示 rate: 500（仅 `RATE 500` 生效，其余失败命令均未改动）
- 是否通过：是

### 19. QUIT 退出

- 输入：`QUIT`
- 预期：程序退出，无额外输出
- 实际：程序退出，无额外输出
- 是否通过：是

### 20. 输入流结束（EOF）

- 输入：`Ctrl+Z` 后回车（或输入文件结束）
- 预期：程序正常退出，不无限打印提示符
- 实际：程序正常退出
- 是否通过：是

## 结论

- 正常、边界、失败三类共 20 组用例全部通过；
- 四类错误（空输入 / 未知命令 / 缺少参数 / 非法参数）可以明确区分；
- 非法修改均保持原配置不变；
- `QUIT` 与 EOF 均可结束程序。
