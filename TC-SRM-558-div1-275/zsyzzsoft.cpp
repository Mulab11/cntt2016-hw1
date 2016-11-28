#include <algorithm>
using namespace std;
const int inf = 1000000000;
class Stamp
{
public:
	int n, c[50][51], f[51];
	int getMinimumCost(string col, int stamp_cost, int push_cost)
	{
		n = col.size();
		int ans = inf;
		for(int i = 0; i < n; i++) //预处理每段区间能否被染成一种颜色 
		{
			c[i][i] = 0;
			for(int j = i + 1; j <= n; j++)
			{
				c[i][j] = c[i][j - 1];
				if(col[j - 1] != '*')
				{
					if(c[i][j] && col[j - 1] != c[i][j])
						c[i][j] = -1;
					else
						c[i][j] = col[j - 1];
				}
			}
		}
		for(int l = 1; l <= n; l++) //枚举染色宽度 
		{
			f[0] = 0;
			for(int i = 1; i <= n; i++) //动态规划 
			{
				f[i] = inf;
				for(int j = i - l; j >= 0 && c[j][i] >= 0; j--)
					f[i] = min(f[i], f[j] + (i - j + l - 1) / l);
			}
			if(f[n] < inf)
				ans = min(ans, l * stamp_cost + f[n] * push_cost);
		}
		return ans;
	}
};
