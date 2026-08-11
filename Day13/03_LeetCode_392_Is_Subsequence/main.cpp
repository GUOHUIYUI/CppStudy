#include <string>

class Solution {
public:
    bool isSubsequence(std::string s, std::string t) {
        int s_index{};
        if (s.size() == 0)return true;
        for (int i = 0;i < t.size();i++)
        {
            if (s[s_index] == t[i])
            {
                s_index++;
            }
            if (s_index == s.size())
            {
                return true;
            }
        }


        return false;
    }
};

int main()
{
    return 0;
}
