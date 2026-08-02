#include <vector>

//class Solution {
//public:
//	int maxProfit(std::vector<int>& prices) {
//		int profit{ 0 };
//		for (int i = 0;i < prices.size() - 1;i++)
//		{
//			for (int j = i + 1;j < prices.size();j++)
//			{
//				if (prices[i] < prices[j])
//				{
//					if (prices[j] - prices[i] > profit)
//					{
//						profit = prices[j] - prices[i];
//					}
//
//				}
//			}
//		}
//		return profit;
//
//	}
//};



/*
	单循环思路   
	需要维护一个最小价格 和最大利润
	如果今天的价格比最小价格低 则更新最小价格
    如果今天的价格比最小价格高 则计算今天的利润 与最大利润比较 如果今天的利润大于最大利润 则更新最大利润	

*/
class Solution {
public:
	int maxProfit(std::vector<int>& prices) {
		
		int miniPrice{prices[0]};
		int maxProfit{ 0 };
		for (int i = 0;i < prices.size();i++)
		{
			const int todayProfit{ prices[i] - miniPrice };
			if (todayProfit > maxProfit)
			{
				maxProfit = todayProfit;
			}
			if (miniPrice > prices[i])
			{
				miniPrice = prices[i];
			}
		}
		return maxProfit;

	}
};

int main()
{
	return 0;
}