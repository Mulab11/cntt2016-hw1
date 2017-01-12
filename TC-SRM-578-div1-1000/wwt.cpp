#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

bool lk[maxn][maxn];
int f[maxn][maxn][maxn][maxn],cost[maxn][maxn],fl[maxn][maxn],n;//memorized

class DeerInZooDivOne
{
public:
	int fa[maxn];

	int get(int a)
	{
		return fa[a] == a ? a : fa[a] = get(fa[a]);
	}

	int max_cost_flow(int s,int t)
	{
		static bool in[maxn];
		static int d[maxn],que[maxn * maxn],pre[maxn];
		int ans = 0;
		for(;;)
		{
			for(int i = 0;i < n;i ++) d[i] = -(1 << 30),in[i] = 0;
			d[s] = 0,in[s] = 1;
			que[1] = s;
			for(int fi = 1,en = 1;fi <= en;fi ++)
			{
				int u = que[fi];
				for(int i = 0;i < n;i ++)
					if (fl[u][i] && d[u] + cost[u][i] > d[i])
					{
						d[i] = d[u] + cost[u][i],pre[i] = u;
						if (!in[i]) que[++ en] = i,in[i] = 1;
					}
				in[u] = 0;
			}
			if (d[t] == -(1 << 30)) break;
			ans += d[t];
			for(int i = t;i != s;i = pre[i])
				fl[i][pre[i]] ++,fl[pre[i]][i] --; 
		}
		return ans;
	}

	int dfs(int u,int fa_u,int v,int fa_v)
	{
		int &tmp = f[u][fa_u][v][fa_v];
		if (~tmp) return tmp;
		for(int i = 0;i < n;i ++)
			if (lk[u][i] && i != fa_u)
				for(int j = 0;j < n;j ++)
					if (lk[v][j] && j != fa_v) dfs(i,u,j,v);
		memset(cost,0,sizeof cost);
		memset(fl,0,sizeof fl);
		for(int i = 0;i < n;i ++)
			if (lk[u][i] && i != fa_u)
			{
				fl[u][i] = 1,cost[u][i] = 0; //i can be u's child
				for(int j = 0;j < n;j ++)
					if (lk[v][j] && j != fa_v)
					{
						fl[j][v] = 1,cost[j][v] = 0;
						fl[i][j] = 1,cost[i][j] = f[i][u][j][v],cost[j][i] = -cost[i][j]; //i matches j
					}
			}
		return tmp = max_cost_flow(u,v) + 1;
	}

	int getmax(vector<int> a,vector<int> b)
	{
		n = a.size() + 1;
		int ans = 0;
		for(int i = 0;i < n - 1;i ++) //enumerate an edge to cut
		{
			memset(lk,0,sizeof lk);
			for(int j = 0;j < n;j ++) fa[j] = j;
			for(int j = 0;j < n - 1;j ++)
				if (i != j)
				{
					lk[a[j]][b[j]] = lk[b[j]][a[j]] = 1;
					fa[get(a[j])] = get(b[j]);
				}
			memset(f,255,sizeof f); //clear the information
			for(int j = 0;j < 2;j ++) //choose one of a[i] and b[i] to be one root
			{
				for(int k = 0;k < n;k ++) //choose another root
					if (get(k) == get(a[i])) 
						ans = max(ans,dfs(k,k,b[i],b[i]));
				swap(a[i],b[i]);
			}
		}
		return ans;
	}
};
