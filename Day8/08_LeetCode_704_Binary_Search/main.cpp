#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

/*
	区间用 [left, right] 闭区间 → 循环条件是 <= → 每次排除 mid 要用 mid ± 1 → mid
	每次都从 left 和 right 重新算。把这四个原则记住，二分查找就不会写错了。
*/
class Solution {
public:
	int search(std::vector<int> &nums, int target) {
		int left = 0;
		int right = static_cast<int>(nums.size()) - 1;
		while (right >= left)
		{
			int mid = left + (right - left) / 2;
			if (nums[mid] == target)
			{
				return mid;
			}
			if (nums[mid] < target)
			{
				left = mid + 1;
			}
			else if (nums[mid] > target) {
				right = mid - 1;

			}
		}
		return -1;
	}


};
int main()
{
	return 0;
}
