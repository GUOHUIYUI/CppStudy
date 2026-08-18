    //class Solution {//暴力解法
    //public:
    //    int mySqrt(int x) {
    //        long long pre{};
    //        int pre_flag{};
    //        int i{};
    //        for (i = 0;i <= x;i++)
    //        {
    //            long long current{};
    //            current = static_cast<long long>(i) * i;
    //            if (current == x)
    //            {
    //                pre_flag = 1;
    //                break;
    //            }
    //            if (pre<x && current>x)
    //            {
    //                break;
    //            }
    //            pre = current;
    //        }
    //        return pre_flag == 1 ? i : i - 1;
    //    }
    //};


class Solution {
public:
    int mySqrt(int x) {
        int left{}, right{ x };
        while (left < right)
        {
            long long mid{ (static_cast<long long>(left) + right + 1) / 2 };
            if (mid * mid <= x)
            {
                left = mid;
            }
            else {
                right = mid - 1;
            }
        }
        return left;

    }
};
int main()
{
    return 0;
}
