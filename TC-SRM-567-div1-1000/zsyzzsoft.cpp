#include <algorithm>
#include <memory.h>
using namespace std;
const int p = 1000000009;
int ans, tot = 1, h[50], f[51];
bool full[10], empty[10], vis[10][50];
class Mountains
{
public:
	int n, m, height[10];
	void Dfs(int depth)
	{
		if(depth == n)
		{
			ans = (ans + tot) % p;
			return;
		}
		int tmp[50] = {0}, cnt = 0;
		memcpy(tmp, h, sizeof(h));
		for(int i = 0; i < m; i++)
		{
			bool flag = true;
			for(int j = 0; j < m; j++)
				flag &= (height[depth] - abs(i - j) > h[j]) == vis[depth][j];
			if(!flag)
				continue;
			for(int j = 0; j < m; j++)
				h[j] = max(h[j], height[depth] - abs(i - j));
			if(full[depth]) //完全可见，记忆化 
				f[h[0]] = (f[h[0]] + tot) % p;
			else if(empty[depth]) //完全不可见，对状态无影响 
				cnt++;
			else //部分可见，最多只有2种可能位置 
				Dfs(depth + 1);
			memcpy(h, tmp, sizeof(h));
		}
		if(empty[depth])
		{
			int last = tot;
			tot = (long long)tot * cnt % p;
			Dfs(depth + 1);
			tot = last;
		}
	}
	int countPlacements(vector<int> heights, vector<string> visibility)
	{
		n = heights.size(), m = visibility[0].size();
		for(int i = 0; i < n; i++)
			height[i] = heights[n - i - 1];
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
				vis[i][j] = visibility[n - i - 1][j] == 'X';
		}
		for(int i = 0; i < n; i++)
		{
			full[i] = empty[i] = true;
			for(int j = 0; j < m; j++)
				full[i] &= vis[i][j], empty[i] &= !vis[i][j];
		}
		Dfs(0);
		for(int i = 0; i < n; i++)
		{
			if(full[i]) //对当前记忆化的结果继续搜索 
			{
				int last[50];
				memcpy(last, f, sizeof(f));
				memset(f, 0, sizeof(f));
				for(int j = 1; j <= 50; j++)
				{
					if(last[j])
					{
						for(int k = 0; k < m; k++)
							h[k] = height[i] - abs(j + k - height[i]);
						tot = last[j];
						Dfs(i + 1);
					}
				}
			}
		}
		return ans;
	}
};
