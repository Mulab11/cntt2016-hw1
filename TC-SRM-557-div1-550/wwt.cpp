/*
很显然原问题就相当于要求个最大反链，但这是一个有环的图，那么最大反链!=最小链覆盖，稍加观察，假如有环，
那么我们在做最小链覆盖的时候相当于用0的代价把一个环覆盖掉了，那么这时候“最小链覆盖”依然等于最大反链，所以直接传递闭包后匹配即可。
*/
#include <bits/stdc++.h>

using namespace std;

class Incubator
{
public:
	bool g[55][55],vis[55];
	int ly[55],n;

	int dfs(int now)
	{
		for(int i = 0;i < n;i ++)
			if (!vis[i] && g[now][i])
			{
				vis[i] = 1;
				if (!ly[i] || dfs(ly[i] - 1)) 
				{
					ly[i] = now + 1;
					return 1;
				}
			}
		return 0;
	}

	int maxMagicalGirls(vector<string> love)
	{
		n = love.size();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++) 
				if (love[i][j] == 'Y') g[i][j] = 1;
		for(int k = 0;k < n;k ++)
			for(int i = 0;i < n;i ++)
				for(int j = 0;j < n;j ++)
					g[i][j] |= g[i][k] & g[k][j]; //传递闭包
		int ans = n;
		for(int i = 0;i < n;i ++)
		{
			memset(vis,0,sizeof vis);
			ans -= dfs(i);
		}
		return ans;
	}
};
