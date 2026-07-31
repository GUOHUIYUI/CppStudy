#include <iostream>
#include <vector>
#include <unordered_map>
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
            for (int j = i;j < (static_cast<int>(nums.size()));j++)
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