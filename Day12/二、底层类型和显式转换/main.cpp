#include <cstdint>
#include <iostream>
#include <string_view>

//需要与协议字段或寄存器宽度对应是，可以指定底层类型
enum class ErrorCode : std::uint8_t {
    none=0,
    invalidCommand=1,
    invalidData=2,
    busy=4
};

enum class ParseResult :std::uint8_t {
    ok,
    emptyInput,
    unknowCommand
};

//位标志适合“多个能力可以同时成立”的情况 如果值是互斥状态，就不要设计成位标志；如果多个开关可同时存在，才考虑位标志。
enum class Permission : std::uint8_t {
    none = 0,
    read = 1,
    write = 2,
    execute = 4
};

ParseResult validateCommand(std::string_view command)
{
    if (command.empty()) return  ParseResult::emptyInput;
    if (command != "START" && command != "STOP") {
        return ParseResult::unknowCommand;
    }
    return ParseResult::ok;
}

int main()
{
    //强类型枚举不会自动转换为整数 应显式转换
    const auto raw = static_cast<std::uint8_t>(ErrorCode::busy);
   
    std::cout << raw << "\n";

    return 0;
}
