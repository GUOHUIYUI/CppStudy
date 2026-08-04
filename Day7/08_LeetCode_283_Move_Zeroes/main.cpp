#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>


/*
    将0元素移动到数组末尾
    思路：将写入位置和读取位置区分开
        一个指针指向写入位置一个指针指向读取位置
        如果读取位置的元素不为0，则将读取位置的元素写入写入位置，并将写入位置后移一位，读取位置不变
        如果读取位置的元素为0，则读取位置后移一位，写入位置不变
*/

class Solution {
public:
    void moveZeroes(std::vector<int>& nums) {
        int write{};
        for (int i = 0;i < nums.size();i++)
        {
            if (nums[i] != 0)
            {
                nums[write] = nums[i];
                if (write != i)
                {
                    nums[i] = 0;
                }
                write++;

            }
        }
    }
};


int main()
{
	return 0;
}
