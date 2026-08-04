#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include<unordered_set>


//class Solution {
//public:
//    bool containsDuplicate(std::vector<int> &nums) {
//        for (int i = 0;i < nums.size()-1;i++)
//        {
//            for (int j = i+1;j < nums.size();j++)
//            {
//                if (nums[i] == nums[j])
//                    return true;
//            }
//        }
//        return false;
//
//
//    }
//};
/*
        std::unordered_set<int> set 定义一个哈希集合
        set.count(num) 存在时返回1，不存在返回0
        set.insert(num) 插入集合
        
         for (int values:nums)增强for循环  values为数组中的元素不是下标
        {
            if(set.count(values))
            {
                return true;
            }
            set.insert(nums[values]);
        }

*/
class Solution {
public:
    bool containsDuplicate(std::vector<int> &nums) {
        std::unordered_set<int> set;
        for (int values:nums)
        {
            if(set.count(values))
            {
                return true;
            }
            set.insert(values);
        }
        return false;


    }
};
int main()
{
    return 0;
}