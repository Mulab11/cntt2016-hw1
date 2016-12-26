/*
把圆锥的横截面拉出来，那么就只需要考虑三角形了。一个圆锥a能放到b上，首先要r_a < r_b，其次，两个圆锥的顶端不能碰到，把三角形画出来，
可以得到一个相似三角形，就能求出b插入a中的高度，判断是否比a的高度小即可。最后跑个二分图匹配。
*/
#include <bits/stdc++.h>

using namespace std;

class PointyWizardHats
{
public:
	bool lk[105][105],vis[105];
	int n,m,ly[105];

	bool ok(long long h_1,long long r_1,long long h_2,long long r_2)
	{
		if (r_1 >= r_2) return 0;
		return r_1 * h_2 < h_1 * r_2; //能放进去
	}

	bool dfs(int now) //匹配
	{
		for(int i = 0;i < m;i ++)
			if (lk[now][i] && !vis[i])
			{
				vis[i] = 1;
				if (!ly[i] || dfs(ly[i] - 1)) {ly[i] = now + 1;return 1;}
			}
		return 0;
	}

	int getNumHats(vector<int> topHeight,vector<int> topRadius,vector<int> bottomHeight,vector<int> bottomRadius)
	{
		n = topHeight.size(),m = bottomRadius.size();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				lk[i][j] = ok(topHeight[i],topRadius[i],bottomHeight[j],bottomRadius[j]);
		int ans = 0;
		for(int i = 0;i < n;i ++)
		{
			memset(vis,0,sizeof vis);
			ans += dfs(i);
		}
		return ans;
	}
};
