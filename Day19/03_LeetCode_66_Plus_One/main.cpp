#include <vector>
using std::vector;
//从后往前去计算，如果不需要进位则加完直接返回 需要进位则将当前位置写0让前一位去加。如果类似9999的元素则创建新数组将第一位置1即可
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        for (int i = digits.size() - 1;i >= 0;i--)
        {
            if (digits[i] == 9 && i == 0)
            {
                vector<int> nums(digits.size() + 1, 0);
                nums[0] = 1;
                return nums;
            }
            if (digits[i] != 9)
            {
                digits[i] += 1;
                break;
            }
            else
            {
                digits[i] = 0;
            }

        }
        return digits;
    }
};

int main()
{
    return 0;
}
