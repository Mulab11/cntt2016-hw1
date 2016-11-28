#include <algorithm>
using namespace std;
class CosmicBlocks
{
public:
	int n, ans, min_ways, max_ways, a[6], h[6], edge[6];
	bool Check()
	{
		int in[6] = {0}, out[6] = {0};
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if((edge[i] >> j) & 1)
					out[i]++, in[j]++;
			}
		}
		for(int i = 0; i < n; i++)
		{
			if(a[i] < in[i] || a[i] < out[i]) //连接数超过了总数 
				return false;
		}
		for(int i = 1; i < 1 << n; i++) //一种合法的方案满足，对于所有相同高度的颜色子集，子集中的总数均不超过下一层连接的总数 
		{
			int flag = -1;
			for(int j = 0; j < n; j++)
			{
				if((i >> j) & 1)
				{
					if(flag == -1)
						flag = h[j];
					else if(flag != h[j])
						flag = 0;
				}
			}
			if(!flag) //高度不相同 
				continue;
			int st = 0, sum = 0;
			for(int j = 0; j < n; j++)
			{
				if((i >> j) & 1)
					st |= edge[j], sum += a[j] - out[j];
			}
			for(int j = 0; j < n; j++)
			{
				if((st >> j) & 1)
					sum -= a[j] - in[j];
			}
			if(sum > 0)
				return false;
		}
		int dp[1 << 6] = {0};
		dp[0] = 1;
		for(int i = 0; i < 1 << n; i++) //动态规划求出消去的方案数 
		{
			int st = 0;
			for(int j = 0; j < n; j++)
			{
				if((i >> j) & 1)
					st |= edge[j];
			}
			for(int j = 0; j < n; j++)
			{
				if((i >> j) & 1 && !((st >> j) & 1)) //颜色在顶端 
					dp[i] += dp[i - (1 << j)];
			}
		}
		return dp[(1 << n) - 1] >= min_ways && dp[(1 << n) - 1] <= max_ways;
	}
	void EnumEdge(int depth)
	{
		if(depth == n)
			ans += Check(); //判断是否合法 
		else if(h[depth])
		{
			for(int i = 1; i < 1 << n; i++) //枚举当前颜色在哪些颜色上方出现 
			{
				bool flag = true;
				for(int j = 0; j < n; j++)
				{
					if((i >> j) & 1 && h[j] + 1 != h[depth])
						flag = false;
				}
				if(!flag)
					continue;
				edge[depth] = i;
				EnumEdge(depth + 1);
			}
		}
		else
			edge[depth] = 0, EnumEdge(depth + 1);
	}
	void EnumHeight(int depth)
	{
		if(depth == n)
			EnumEdge(0); //然后再枚举相邻高度间的连接方式 
		else
		{
			for(int i = 0; i < n; i++)
				h[depth] = i, EnumHeight(depth + 1);
		}
	}
	int getNumOrders(vector<int> a_vec, int _min_ways, int _max_ways)
	{
		n = a_vec.size();
		min_ways = _min_ways, max_ways = _max_ways;
		for(int i = 0; i < n; i++)
			a[i] = a_vec[i];
		ans = 0;
		EnumHeight(0); //枚举每种颜色的高度 
		return ans;
	}
};
