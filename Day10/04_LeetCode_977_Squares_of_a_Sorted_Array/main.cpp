#include <iostream>
#include <vector>


/*
    size_t 是无符号整数（unsigned），当 tail 减到 0 后再执行 tail--，会发生下溢，tail 从 0 变成 SIZE_MAX（一个巨大的正数)
    std::vector<type> 数组名
        常用用法： std::vector<type> nums{1,2,3};
                 std::vector<type> nums{};
                 std::vector<type> nums(length);
                 std::vector<type> nums(nums2);
                 std::vector<type> nums=nums2;

*/

class Solution {
public:
    std::vector<int> sortedSquares(std::vector<int> &nums) {
        int count = nums.size();
        std::vector<int> nums1(count);
        int head{};
        //size_t tail = nums.size() - 1;   
        //size_t index = nums.size() - 1;
        int tail = nums.size() - 1;
        int index = nums.size() - 1;
        while (head <= tail)
        {
            if (std::abs(nums[head]) <= std::abs(nums[tail]))
            {
                nums1[index--] = nums[tail] * nums[tail];
                tail--;
            }
            else if (std::abs(nums[head]) > std::abs(nums[tail]))
            {
                nums1[index--] = nums[head] * nums[head];
                head++;
            }
        }
        return nums1;

    }
};

int main()
{
    return 0;
}
