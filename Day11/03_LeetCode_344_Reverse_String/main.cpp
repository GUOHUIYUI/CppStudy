#include <vector>

//思路: 双指针指向头尾，交换指向的元素，然后指针向中间靠拢，知道指针相遇，则完成翻转
class Solution {
public:
	void reverseString(std::vector<char>& s) {
		int left = 0;
		int right = s.size() - 1;
		while (left < right)
		{
			char tmp = s[left];
			s[left] = s[right];
			s[right] = tmp;
			left++;
			right--;
		}


	}
};



int main()
{
	return 0;
}
