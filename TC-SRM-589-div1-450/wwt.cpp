#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

class GearsDiv1
{
public:
	int c[maxn],lx[maxn],n,ans;
	bool lk[maxn][maxn],vis[maxn];

	int find(int x)
	{
		for(int i = 0;i < n;i ++)
			if (lk[x][i] && !vis[i])
			{
				vis[i] = 1;
				if (lx[i] == -1 || find(lx[i])) 
					return lx[i] = x,1;
			}
		return 0;
	}

	int getmin(string color, vector <string> graph)
	{
		int ans = 0;
		n = graph.size();
		for(int i = 0;i < n;i ++)
			if (color[i] == 'R') c[i] = 0; else 
				if (color[i] == 'B') c[i] = 1; else c[i] = 2;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				ans += (graph[i][j] == 'Y');
		for(int i = 0;i < 3;i ++) //enumerate the color that has different direction from others.
		{
			memset(lk,0,sizeof lk),memset(lx,255,sizeof lx);
			for(int j = 0;j < n;j ++)
				if (c[j] == (i + 1) % 3) 
					for(int k = 0;k < n;k ++)
						if (c[k] == (i + 2) % 3 && graph[j][k] == 'Y') lk[j][k] = 1; //another two colors may have arguement
			int cur = 0;
			//in a bipartite graph,minimum vertex cover is equal to maximum matching
			for(int j = 0;j < n;j ++)
				if (c[j] == (i + 1) % 3)
				{
					memset(vis,0,sizeof vis);
					cur += find(j);
				}
			ans = min(ans,cur);
		}
		return ans;
	}
};
