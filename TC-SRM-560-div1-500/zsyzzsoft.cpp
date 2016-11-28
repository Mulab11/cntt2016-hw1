#include <algorithm>
using namespace std;
class DrawingPointsDivOne
{
	static const int l = 300;
	int pt[l][l], dp[l][l];
public:
	bool Simulate(int k)
	{
		for(int i = l - 1; i > 0; i--) //模拟 
		{
			for(int j = l - 1; j > 0; j--)
			{
				if(!pt[i][j])
					pt[i][j] = pt[i - 1][j] || pt[i][j - 1] || pt[i - 1][j - 1];
			}
		}
		for(int i = l - 2; i > 0; i--) //动态规划求正方形最大边长 
		{
			for(int j = l - 2; j > 0; j--)
			{
				dp[i][j] = pt[i][j] ? min(dp[i + 1][j + 1], min(dp[i + 1][j], dp[i][j + 1])) + 1 : 0;
				if(pt[i][j] < 2 && dp[i][j] > k)
					return false;
			}
		}
		return true;
	}
	int maxSteps(vector<int> x, vector<int> y)
	{
		for(int i = 0; i < x.size(); i++)
			pt[x[i] + 71][y[i] + 71] = 2;
		for(int k = 1; k <= 150; k++)
		{
			if(!Simulate(k)) //按步模拟，判断是否存在不以初始点为中心的边长为k的正方形 
				return k - 1;
		}
		return -1;
	}
};
