#include <array>
#include <string>

//使用增强for循环 依次遍历两个字符串   遍历第一个字符串在数组中记录每个字符出现的次数   遍历第二个字符串将对应字符串出现的次数-1   遍历完成后遍历维护的字符出现次数数组，有大于0元素即返回false
class Solution {
public:
    bool canConstruct(std::string ransomNote, std::string magazine) {
        std::array<int, 26> arr{};
        for (char value : ransomNote)
        {
            arr[value - 'a']++;
        }
        for (char value : magazine)
        {
            arr[value - 'a']--;
        }
        for (int a : arr)
        {
            if (a > 0)
                return false;
        }
        return true;
    }
};

int main()
{
    return 0;
}
