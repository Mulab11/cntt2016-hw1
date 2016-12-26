#include <algorithm>
using namespace std;
class RandomPaintingOnABoard
{
public:
	double expectedSteps(vector<string> prob)
	{
		int n = prob.size(), m = prob[0].size(), a[12][21], sum = 0;
		if(n < m)
		{
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < m; j++)
					sum += a[i][j] = prob[i][j] - '0';
			}
		}
		else
		{
			swap(n, m);
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < m; j++)
					sum += a[i][j] = prob[j][i] - '0';
			}
		}
		double ans = 0.0;
		for(int i = 1; i <= 1 << n; i++) //枚举选择了哪些行 
		{
			int f[22][1351][2] = {0}, cnt = 0;
			for(int k = 0; k < n; k++)
				cnt += (i >> k) & 1;
			f[0][0][((n + m) & 1) ^ (cnt & 1)] = 1;
			for(int j = 0; j < m; j++) //只关心选出部分的和，以及列数的奇偶性，可以dp求出 
			{
				int s = 0;
				for(int k = 0; k < n; k++)
				{
					if((i >> k) & 1)
						s += a[k][j];
				}
				for(int k = 0; k <= sum; k++)
				{
					for(int t = 0; t <= 1; t++)
					{
						if(f[j][k][t])
						{
							f[j + 1][k][t] += f[j][k][t];
							f[j + 1][k + s][t ^ 1] += f[j][k][t];
						}
					}
				}
			}
			for(int j = 0; j < sum; j++)
			{
				double p = (double)j / sum; //每一轮的期望累加项形如公比为p的无穷数列 
				ans += p / (1.0 - p) * (f[m][j][1] - f[m][j][0]);
			}
		}
		return ans + 1.0;
	}
};