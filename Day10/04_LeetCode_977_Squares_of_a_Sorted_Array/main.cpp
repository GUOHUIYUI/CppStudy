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


/*
    思路：数组本身有序，平方后最大值只可能在数组两端出现
            使用两个指针指向数组的两端，比较绝对值较大的值平方后即为最大值，插入到目标数组的末尾，然后移动对应的指针

*/
class Solution {
public:
    std::vector<int> sortedSquares(std::vector<int> &nums) {
        
        std::vector<int> result(nums.size());
        int head{};
        //size_t tail = nums.size() - 1;   
        //size_t index = nums.size() - 1;
        int tail = nums.size() - 1;
        int index = nums.size() - 1;
        while (head <= tail)
        {
            if (std::abs(nums[head]) <= std::abs(nums[tail]))
            {
                result[index--] = nums[tail] * nums[tail];
                tail--;
            }
            else if (std::abs(nums[head]) > std::abs(nums[tail]))
            {
                result[index--] = nums[head] * nums[head];
                head++;
            }
        }
        return result;

    }
};

int main()
{
    return 0;
}
