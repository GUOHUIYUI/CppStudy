#include <string>
#include <vector>


//思路解析：以第一个字符串的长度为外层循环  以数组长度为内层循环   依次比对后续字符串对应位置的字符和第一个字符串对应位置的字符
//遍历通过则将该字符添加到需要返回的字符，不相符则直接返回

class Solution {
public:
    static std::string longestCommonPrefix(std::vector< std::string>& strs) {
        std::string str{};
        for (int i = 0;i < strs[0].size();i++)
        {
            for (int j = 0;j < strs.size();j++)
            {
                if (strs[0][i] != strs[j][i])
                    return str;
            }
            str += strs[0][i];
        }
        return str;

    }
};

int main()
{
    std::vector<std::string> strs = { "flower", "flow", "flight" };
    Solution::longestCommonPrefix(strs);
    return 0;
}
