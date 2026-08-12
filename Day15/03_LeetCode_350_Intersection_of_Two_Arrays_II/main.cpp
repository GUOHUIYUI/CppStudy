#include <vector>
#include<algorithm>

//先对两个数组进行排序，排序后使用两个指针分别指向两个数组，两个元素相同则同步移动两个指针，不同则移动较小值的指针

class Solution {
public:
	std::vector<int> intersect(std::vector<int> &nums1, std::vector<int> &nums2) {
		std::vector<int> nums;
		std::sort(nums1.begin(),nums1.end());
		std::sort(nums2.begin(), nums2.end());
		std::size_t nums1_index{}, nums2_index{};
		while (nums1_index < nums1.size() && nums2_index < nums2.size())
		{
			if (nums1[nums1_index] == nums2[nums2_index])
			{
				nums.push_back(nums1[nums1_index]);
				nums1_index++;
				nums2_index++;
			}
			else
			{
				nums1[nums1_index] < nums2[nums2_index] ? nums1_index++ : nums2_index++;
			}
		}

		return nums;
		}
};

int main()
{
	return 0;
}
