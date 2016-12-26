/*
首先，假如把点都选出来的， 那么ans = 2 * |e| - maxdis,|e|表示虚树的边，maxdis表示最长链的长度。那么E[ans]=2E[|e|]-E[maxdis]，
E[|e|]直接考虑每条边的贡献，一条边会存在等价于他上面和下面都有点，那么总的减掉只有上面或下面有点的情况即可。
E[maxdis]就不是那么好求了。考虑一对点(u,v)什么时候会成为最长链？假如存在另外一个点k，使得dis(u,k)>dis(u,v)或dis(v,k)>dis(u,v)时，
那么(u,v)显然不是最长链，那么假如不存在呢，(u,v)必然是最长链，证明：设最长链为(x,y)，联想求最长链的做法，以u为根，
找到深度最大的点，再找深度最大的点，那么假如(x,y)为最长链，必有(u,x)或(u,y)为以u为根深度最大的点，
与dis(u,x)<dis(u,v)且dis(u,y)<dis(u,v)矛盾，于是得证。那么对于一对(u,v)，统计有多少点是不能选的，剩下的点都可以选，组合数算一下就好了。
*/
#include <bits/stdc++.h>

using namespace std;

const int maxn = 2505;

const int xy[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

double ans,c[305][305];
int ord[55][55],tot;
int final[maxn],to[maxn * 8],nex[maxn * 8],d[305][305],po[maxn],siz[maxn],cnt,star,__k;

class Orienteering
{
public:
	int ref[maxn];

	void link(int u,int v)
	{
		to[++ tot] = v,nex[tot] = final[u],final[u] = tot;
	}

	void dfs(int top,int now,int pre,int dis)
	{
		if (top && ref[now]) d[top][ref[now]] = dis;
		siz[now] = bool(ref[now]);
		for(int i = final[now];i;i = nex[i])
			if (to[i] != pre) dfs(top,to[i],now,dis + 1),siz[now] += siz[to[i]];
		if (!top && pre)
			ans += 2 * (c[star][__k] - c[siz[now]][__k] - c[star - siz[now]][__k]); //求E[|e|]，统计经过now到pre这条边的集合数
	}

	bool better(int s,int a,int b) //s->a这条路比b->a好
	{
		if (d[s][a] > d[a][b]) return 1;
		if (d[s][a] == d[a][b])
		{
			int x = s,y = a;
			if (x > y) swap(x,y);
			if (a > b) swap(a,b);
			if (x < a || x == a && y < b) return 1;
		}
		return 0;
	}

	double expectedLength(vector<string> field, int K)
	{
		__k = K;
		for(int i = 0;i <= 300;i ++)
		{
			c[i][0] = 1;
			for(int j = 1;j <= i;j ++) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
		ans = 0;
		cnt = tot = star = 0;
		memset(final,0,sizeof final);memset(ref,0,sizeof ref);
		for(int i = 0;i < field.size();i ++)
			for(int j = 0;j < field[i].length();j ++)
				if (field[i][j] != '#')
				{ 
					ord[i][j] = ++ cnt;
					if (field[i][j] == '*') ref[cnt] = ++ star,po[star] = cnt;
				}
		for(int i = 0;i < field.size();i ++)
			for(int j = 0;j < field[i].length();j ++)
				if (field[i][j] != '#')
					for(int x = 0;x < 4;x ++)
						{
							int nx = i + xy[x][0],ny = j + xy[x][1];
							if (nx >= 0 && ny >= 0 && nx < field.size() && ny < field[i].length() && ord[nx][ny])
								link(ord[i][j],ord[nx][ny]); //建树
						}
		dfs(0,1,0,0);
		for(int i = 1;i <= star;i ++)
			dfs(i,po[i],0,0);
		for(int u = 1;u <= star;u ++)
			for(int v = u + 1;v <= star;v ++) //以u,v为半径
			{
				int ok = star - 2;
				for(int i = 1;i <= star;i ++)
					if (i != u && i != v)
						if (better(i,u,v) || better(i,v,u)) ok --; //i这个点不能存在
				if (__k >= 2)
					ans -= d[u][v] * c[ok][__k - 2];
			}
		return ans / c[star][__k]; //求的是期望
	}
};
