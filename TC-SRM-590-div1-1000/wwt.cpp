#include <bits/stdc++.h>

using namespace std;

const int maxn = 45 * 45;

struct node
{
	int to,next,flow;

	node(void){}
	node(int a,int b,int c) : to(a),next(b),flow(c){}
}e[maxn * 45 * 2];

class FoxAndCity
{
public:
	int ref[45][45],final[maxn],count[maxn],d[maxn],cnt,s,t,n,tot;

	int dfs(int now,int flow)
	{
		if (now == t) return flow;
		int use = 0;
		for(int i = final[now];i;i = e[i].next)
			if (e[i].flow > 0 && d[e[i].to] + 1 == d[now])
			{
				int tmp = dfs(e[i].to,min(flow - use,e[i].flow));
				e[i].flow -= tmp,e[i ^ 1].flow += tmp,use += tmp;
				if (flow == use) return use;
			}
		if (!(-- count[d[now]])) d[s] = t + 1;
		++ count[++ d[now]];
		return use;
	}

	void link(int u,int v,int f)
	{
		e[++ tot] = node(v,final[u],f),final[u] = tot;
		e[++ tot] = node(u,final[v],0),final[v] = tot;
	}

	int minimalCost(vector<string> linked, vector<int> want)
	{
		memset(final,0,sizeof final);
		tot = 1;
		n = want.size();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j <= n;j ++) ref[i][j] = ++ cnt; //the point that means d[i] = j
		s = 0,t = ++ cnt;
		for(int i = 0;i < n;i ++)
		{
			link(s,ref[i][0],1 << 30);
			for(int j = 0;j <= n;j ++)
			{
				int nxt = (j < n) ? ref[i][j + 1] : t,c;
				if (!i && j || i && !j) c = (1 << 30); else c = (j - want[i]) * (j - want[i]);
				link(ref[i][j],nxt,c); //the cost if d[i] = j
			}
		}
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				if (linked[i][j] == 'Y') //there is an edge from i to j,which implies that d[j]-1<=d[i]
					for(int d = 1;d <= n;d ++) //d[j] = d
					{
						//i must be cut after d[j]-1
						link(ref[j][d],ref[i][d - 1],1 << 30);
					}
		int ans = 0;
		memset(count,0,sizeof count),memset(d,0,sizeof d);
		count[0] = t + 1;
		for(;d[s] < t + 1;ans += dfs(s,1 << 30));
		return ans;			
	}	
};
