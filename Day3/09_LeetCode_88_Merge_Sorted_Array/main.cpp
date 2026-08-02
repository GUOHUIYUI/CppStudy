#include <iostream>
#include <vector>

class Solution {
public:
	void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n)
	{
		int i{ m - 1 }; // nums1的最后一个元素的索引
		int j{ n - 1 }; // nums2的最后一个元素的索引
		//int write{ nums1.size() - 1 }; //nums1的最后一个位置的索引
		int write{ m + n - 1 };
		while (i >= 0 && j >= 0)
		{
			if (nums1[i] > nums2[j])
			{
				nums1[write] = nums1[i];
				i--;
			}
			else
			{
				nums1[write] = nums2[j];
				j--;
			}
			write--;
		}
		if (i < 0)
		{
			while (j >= 0)
			{
				nums1[write] = nums2[j];
				j--;
				write--;
			}
		}
	}
};



int main()
{
	return 0;
}