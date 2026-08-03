#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


/* 思路解析 */
// 如果两个字符串长度不相同，直接返回false
// 将字符 - 'a'当作下标 遍历第一个数组时记录每个字符出现的数量
// 遍历第二个数组时没遇到一个字符就将相应的下标的数量减一
// 最后遍历整个数组，只要有一个元素的个数不为0则返回false
class Solution {
public:
    bool isAnagram(std::string s,std:: string t) {
        int index[26]{};
        
        if (s.size() != t.size())
        {
            return false;
        }
        for (char current : s)
        {
            ++index[current - 'a'];
        }
        for (char current : t)
        {
            --index[current - 'a'];
        }
        for (int i = 0;i < 26;i++)
        {
            if (index[i] != 0)
            {
                return false;
            }
        }

        return true;

    }
};



int main()
{
    return 0;
}
