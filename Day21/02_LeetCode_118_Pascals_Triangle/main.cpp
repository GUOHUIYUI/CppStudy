#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> generate(int numRows)
    {
        // TODO: 在LeetCode完成实现。
        std::vector<std::vector<int>> nums(numRows);//二维数组的声明
        for (int i = 0;i < numRows;i++)
        {
            nums[i].resize(i + 1, 1);
            for (int j = 1;j < nums[i].size()-1;j++)
            {
                nums[i][j] = nums[i - 1][j] + nums[i - 1][j - 1];
            }
        }
        return nums;
    }
};

int main()
{
    return 0;
}
