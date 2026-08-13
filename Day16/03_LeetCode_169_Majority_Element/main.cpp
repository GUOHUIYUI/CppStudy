#include <vector>
#include<algorithm>
//思路解析：先排序数组  然后对遍历每个元素时记录出现次数并判断是否出现过足够的次数，次数足够直接返回，如果后一个元素与前一个不一样则清空计数。
class Solution {
public:
    int majorityElement(std::vector<int> &nums) {
        std::sort(nums.begin(), nums.end());
        int count{};
        int pre{};
        for (int num : nums)
        {
            if (num != pre)count = 0;
            pre = num;
            count++;
            if (count * 2 > nums.size())
            {
                return num;
            }
        }
        return pre;
    }
};
int main()
{
    Solution s{};
    std::vector<int> nums{ 3,3,4 };
    s.majorityElement(nums);
    return 0;
}
