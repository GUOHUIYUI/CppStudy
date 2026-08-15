#include <vector>


//思路：将范围内的所有元素加起来，再和数组中的元素作差，最后剩下的即为数组中未出现的

class Solution {
public:
    int missingNumber(std::vector<int>& nums) {
        int sum{};
        for (int i = 0;i <= nums.size();i++)
        {
            sum += i;
        }
        for (int value : nums)
        {
            sum -= value;
        }
        return sum;
    }
};

int main()
{
    return 0;
}
