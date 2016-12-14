#include <algorithm>
#include <memory.h>
using namespace std;
const int inf = 1000000000;
class WallGameDiv1
{
public:
	int n, m, sum[50][50][50], f[50][50][50];
	int Dfs(int i, int j, int k)
	{
		if(j < 0 || j >= m)
			return inf;
		if(i == n - 1)
			return sum[i][j][j];
		if(f[i][j][k] >= 0)
			return f[i][j][k];
		if(j < k) //如果断开了与下一层的连接，有两种选择，继续向当前方向走或者绕到另一边 
			f[i][j][k] = min(sum[i][j][j] + Dfs(i, j - 1, k), sum[i][j][k] + Dfs(i, k + 1, j));
		else
			f[i][j][k] = min(sum[i][j][j] + Dfs(i, j + 1, k), sum[i][j][k] + Dfs(i, k - 1, j));
		if(f[i][j][k] >= inf)
			f[i][j][k] = 0;
		return f[i][j][k] = max(f[i][j][k], sum[i][j][j] + Dfs(i + 1, j, j)); //如果允许走到下一层 
	}
	int play(vector<string> map)
	{
		n = map.size(), m = map[0].length();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				map[i][j] -= '0';
		}
		for(int i = 0; i < n; i++) //前缀和 
		{
			for(int j = 0; j < m; j++)
			{
				sum[i][j][j] = map[i][j];
				for(int k = j - 1; k >= 0; k--)
					sum[i][j][k] = sum[i][j][k + 1] + map[i][k];
				for(int k = j + 1; k < m; k++)
					sum[i][j][k] = sum[i][j][k - 1] + map[i][k];
			}
		}
		memset(f, -1, sizeof(f));
		int ans = inf;
		for(int i = 0; i < m; i++) //枚举起点，记忆化搜索 
			ans = min(ans, Dfs(0, i, i));
		return ans;
	}
};