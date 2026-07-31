#include <iostream>
#include <vector>
#include <unordered_map>

//std::vector<int> nums{2, 7, 11, 15};  声明不定长数组  可以使用下标访问
//nums.size() 获取数组长度
//return { 1,2 };
//auto 关键字 编译器自动推导类型  例如 auto x = 5; // x的类型为int
//std::unordered_map <int, int > num_map;  声明一个unordered_map  存储int到int的映射   <int,int> 表示键值对的类型  第一个int是键的类型  第二个int是值的类型
//哈希表的核心作用是通过哈希函数将键映射到数组的索引，从而实现快速查找、插入和删除操作。哈希表的平均时间复杂度为O(1)，最坏情况下为O(n)，但在实际应用中，哈希表通常表现出非常高效的性能。
/*
	std::unordered_map <int, int > num_map 键值对 键存放数组的值 值存放数组的索引
	num_map(find)从哈希表中查找对应的值  查找到返回一个迭代器  如果没有找到 返回end()迭代器
	因此if(found != num_map.end())表示如果找到了对应的值 
	返回return { found->second,i };  返回一个数组  found->second是找到的值的索引  i是当前值的索引


*/

//class Solution {
//public:
//    std::vector<int> twoSum(
//        std::vector<int> &nums,
//        int target
//    ) {
//        std::unordered_map <int, int > num_map;//存储数字及其索引
//
//		for (int i = 0;i < static_cast<int>(nums.size());++i)
//		{
//			const int complement = target - nums[i];
//            const auto found = num_map.find(complement);
//
//            if (found != num_map.end())
//            {
//                return  { found->second,i };
//            }
//			num_map[nums[i]] = i;
//			
//		}
//        return {};
//
//
//    }
//};
class Solution {
public:
    std::vector<int> twoSum(
        std::vector<int> &nums,
        int target
    ) {
        for (int i = 0;i < (static_cast<int>(nums.size()));i++)
        {
            //for (int j = i;j < (static_cast<int>(nums.size()));j++)
			for (int j = i + 1;j < (static_cast<int>(nums.size()));j++) //j从i+1开始 避免重复计算
            {
				if (nums[i] + nums[j] == target && i != j)
				{
					return { i,j };
				}
            }

       }


    }
};
int main()
{
    std::cout << "Hello, world!\n";

    return 0;
}