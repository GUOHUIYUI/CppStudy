#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


class Solution {
public:
    int searchInsert(std::vector<int> &nums, int target) {
        int left{ 0 };
        int right = nums.size() - 1;
        while (right >= left)
        {
            int mid = left + (right - left + 1) / 2;   //中间值计算原理：(right - left + 1)/2得到剩下区间的一半，还需要加上当前区间的起始位置。
            if (nums[mid] == target)
            {
                return mid;
            }
            if (nums[mid] < target)
            {
                left = mid + 1;
            }
            else if (nums[mid] > target)
            {
                right = mid - 1;
            }
        }
        //程序结束时，right一定小于left。left左边一定小于目标值，右边一定大于目标值，所以left即为目标位置。
        return left;
    }
};

int main()
{
    return 0;
}
