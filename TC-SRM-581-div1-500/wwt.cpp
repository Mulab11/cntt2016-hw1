#include <bits/stdc++.h>

using namespace std;

const int maxn = 305;

class TreeUnion
{
public:
	int fa[2][maxn],dis[2][maxn][maxn];
	int count[2][maxn][maxn],n;// count how many points from which to point i is j edges
	
	void decode(int *fa,vector<string> a)
	{
		int l = 0;
		fa[0] = 0;
		bool exi = 0;int x = 0;
		for(auto i : a) for(auto j : i)
		{
			if (j >= '0' && j <= '9') exi = 1,x = x * 10 + j - 48; else
			{
				if (exi) fa[++ l] = x;
				exi = 0,x = 0;
			}
		}
		if (exi) fa[++ l] = x;
		n = l + 1;
	}

	void get_dis(int ty,int root,int now,int pre,int d)
	{
		dis[ty][root][now] = d;
		count[ty][root][d] ++;
		for(int i = 0;i < n;i ++)
			if (i != pre && i != now && (i == fa[ty][now] || fa[ty][i] == now))
				get_dis(ty,root,i,now,d + 1);
	}

	double expectedCycles(vector<string> tree1,vector<string> tree2, int K)
	{
		decode(fa[0],tree1),decode(fa[1],tree2);
		for(int i = 0;i < 2;i ++)
			for(int j = 0;j < n;j ++)
				get_dis(i,j,j,-1,0);
		double ans = 0;
		K -= 2;
		for(int u = 0;u < n;u ++)
			for(int v = u + 1;v < n;v ++) //enumerate two points in treeA
				if (dis[0][u][v] < K)
					for(int eu = 0;eu < n;eu ++) //enumerate the point matches u in treeB
						ans += count[1][eu][K - dis[0][u][v]] / double(n) / double(n - 1);
		return ans;
	}
};
