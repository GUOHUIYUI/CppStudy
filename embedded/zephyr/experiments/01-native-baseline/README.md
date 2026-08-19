# native_sim 环境与时间粒度实验

## 我想验证什么
验证k_sleep()，k_mssleep()与具体休眠时间的关系

## 实际环境
- West：
- Zephyr：
- Board：
- Tick frequency：100
- Tickless：y

## 观察结果
实际休眠时间与设置的休眠时间不一致

## 我现在能够解释什么
zephyr采用整数tick向上取整管理，不记录半个tick，会向上取整
具体的tick时间与Tick frequency有关
## 仍然不能证明什么
native_sim 成功不能证明真实 MCU 上的时钟精度和硬件外设行为
## 下一个问题
