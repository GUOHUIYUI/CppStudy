#include <vector>


//利用异或操作 相同为0不同为1  最后剩下的即为唯一出现一次的元素
class Solution {
public:
    int singleNumber(std::vector<int>& nums) {
        int ret{};
        for (int value : nums)
        {
            ret ^= value;
        }
        return ret;
    }
};

int main()
{
    return 0;
}
