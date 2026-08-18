#ifndef DAY20_COMMAND_PARSER_H
#define DAY20_COMMAND_PARSER_H

#include "device_config.h"

#include <string>
#include <string_view>

// 在这里声明命令结果和命令解析接口。

namespace device {
	// 解析单条命令并应用到配置对象，返回执行结果。
	// SHOW 命令的显示文本写入 output；其余命令 output 保持为空。
	CommandInfo CommandComplier(std::string_view cmd, DeviceConfig& device, std::string& output);
}

#endif
