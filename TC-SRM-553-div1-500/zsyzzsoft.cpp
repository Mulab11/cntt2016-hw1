#include <algorithm>
using namespace std;
const int p = 1000000007;
class TwoConvexShapes
{
public:
	int n, m, map[50][50];
	bool CheckFull(int h)
	{
		for(int i = 0; i < h; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(map[i][j] == 0)
					return false;
			}
		}
		for(int i = h; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				if(map[i][j] == 1)
					return false;
			}
		}
		return true;
	}
	void ReverseV()
	{
		for(int i = 0; i < n / 2; i++)
		{
			for(int j = 0; j < m; j++)
				swap(map[i][j], map[n - i - 1][j]);
		}
	}
	void ReverseH()
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m / 2; j++)
				swap(map[i][j], map[i][m - j - 1]);
		}
	}
	int Work()
	{
		int f[51][51] = {0}, lo[51] = {0}, hi[51] = {0};
		for(int i = 0; i < n; i++) //计算每行的最小与最大黑色长度 
		{
			hi[i] = m; 
			for(int j = 0; j < m; j++)
			{
				if(map[i][j] == 1)
					lo[i] = j + 1;
			}
			for(int j = m - 1; j >= 0; j--)
			{
				if(map[i][j] == 0)
					hi[i] = j;
			}
			if(lo[i] > hi[i])
				return 0;
		}
		for(int i = 0; i <= m; i++)
			f[n][i] = 1;
		for(int i = n - 1; i >= 0; i--) //求方案数 
		{
			for(int j = 0; j <= m; j++)
			{
				for(int k = lo[i]; k <= hi[i] && k <= j; k++)
					f[i][j] = (f[i][j] + f[i + 1][k]) % p;
			}
		}
		return f[0][m];
	}
	int countWays(vector<string> grid)
	{
		n = grid.size();
		for(int i = 0; i < n; i++)
		{
			m = grid[i].size();
			for(int j = 0; j < m; j++)
				map[i][j] = grid[i][j] == 'W' ? 0 : grid[i][j] == 'B' ? 1 : -1;
		}
		int ans = Work();
		for(int i = 0; i <= n; i++) //去重 
			ans = (ans + p - CheckFull(i)) % p;
		ReverseV(); //翻转成另一种情况 
		ans = (Work() + ans) % p;
		for(int i = 0; i <= n; i++)
			ans = (ans + p - CheckFull(i)) % p;
		ReverseH();
		ans = (Work() + ans) % p;
		for(int i = 0; i <= n; i++)
			ans = (ans + p - CheckFull(i)) % p;
		ReverseV();
		ans = (Work() + ans) % p;
		for(int i = 0; i <= n; i++)
			ans = (ans + p - CheckFull(i)) % p;
		return (ans + p + CheckFull(0) + CheckFull(n)) % p;
	}
};
