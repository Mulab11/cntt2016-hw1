#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

struct node
{
	int to,next,flow;

	node(void){}
	node(int a,int b,int c) : to(a),next(b),flow(c){}
}e[maxn * maxn * 100];

class BoardPainting
{
public:
	int d[maxn * maxn],co[maxn * maxn];
	int ord[maxn][maxn],final[maxn * maxn],s,t,cnt,tot;

	void link(int u,int v,int f)
	{
		e[++ tot] = node(v,final[u],f),final[u] = tot;
		e[++ tot] = node(u,final[v],0),final[v] = tot;
	}

	int dfs(int now,int flow)
	{
		if (now == t) return flow;
		int use = 0;
		for(int i = final[now];i;i = e[i].next)
			if (e[i].flow > 0 && d[e[i].to] + 1 == d[now])
			{
				int tmp = dfs(e[i].to,min(flow - use,e[i].flow));
				e[i ^ 1].flow += tmp,e[i].flow -= tmp,use += tmp;
				if (flow == use) return use;
			}
		if (!(-- co[d[now]])) d[s] = t + 1;
		++ co[++ d[now]];
		return use;
	}

	int minimalSteps(vector<string> a)
	{
		memset(final,0,sizeof final),memset(ord,0,sizeof ord);
		tot = 1;
		cnt = 0;
		int n = a.size(),m = a[0].length();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (a[i][j] == '#') ord[i][j] = ++ cnt;
		s = 0,t = cnt + 1;
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
				if (a[i][j] == '#')
				{
					int cost_hor = 0;//the cost that this point were a horizonal point
					if (!j || a[i][j - 1] == '.') ++ cost_hor;
					if (j + 1 == m || a[i][j + 1] == '.') ++ cost_hor;
					link(s,ord[i][j],cost_hor);
					int cost_ver = 0;//the cost that this point were a vertical point
					if (!i || a[i - 1][j] == '.') ++ cost_ver;
					if (i + 1 == n || a[i + 1][j] == '.') ++ cost_ver;
					link(ord[i][j],t,cost_ver);
					if (j + 1 < m && ord[i][j + 1]) //if the type of these two points are different then it will make a cost
						link(ord[i][j],ord[i][j + 1],1),link(ord[i][j + 1],ord[i][j],1);
					if (i + 1 < n && ord[i + 1][j]) //the same
						link(ord[i + 1][j],ord[i][j],1),link(ord[i][j],ord[i + 1][j],1);
				}
		int ans = 0;
		memset(d,0,sizeof d),memset(co,0,sizeof co);
		co[0] = t + 1;
		for(;d[s] < t + 1;) ans += dfs(s,1 << 30);
		return ans / 2;// every border is counted twice
	}
};
