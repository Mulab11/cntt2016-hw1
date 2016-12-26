/*
网络流。构图是：假如(u,v)是危桥，那么u<->v流量为2，否则是+oo。接下来，s->s1流量为2an,t1->t流量为2an，s2,t2同理，跑个最大流，
看看是否满流。但直接这样判绝对是错的，因为可能s1->t2或s2->t1这样。那么我们交换一下s1,t1，再跑一遍，假如还是满流，那么就合法。
证明？令f1(e)表示e这条边第一次流的流量（负数表示反着流）,f2(e)表示第二次，那么令fa(e)=(f1(e)+f2(e))/2,
可以发现这样对于s2,t2而言恰好s2出去2bn,t2进来2bn，而s1,t1都是0，同理，令fb(e)=(f1(e)-f2(e))/2，那么s1,t1就合法，s2,t2就都为0，
fc(e)=fa(e)+fb(e)就恰好是一种合法方案。fc(e)可能爆掉cap(e)?(f1(e)+f2(e))/2+|f1(e)-f2(e)|/2 <= max(f1(e),f2(e)) <= cap(e)，所以不会爆。
*/
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int D[MAXN],Count[MAXN],f[58][58],g[58][58],S,T,N,tot;
int a1,a2,an,b1,b2,bn;

void link(int u,int v,int fl)
{
	f[u][v] = fl;
	if (u == S || v == T) fl = 0;
	f[v][u] = fl;
}

int min(int a,int b) {return a < b ? a : b;}

int dfs(int Now,int flow)
{
	if (Now == T) return flow;
	int use = 0;
	for(int i = S;i <= T;i ++)
		if (g[Now][i] && D[i] + 1 == D[Now])
		{
			int k = dfs(i,min(flow - use,g[Now][i]));
			use += k,g[Now][i] -= k,g[i][Now] += k;
			if (use == flow) return use;
		}
	if (!(-- Count[D[Now]])) D[S] = T + 1;
	Count[++ D[Now]] ++;
	return use;
}

int maxflow()
{
	memset(D,0,sizeof D);memset(Count,0,sizeof Count);memcpy(g,f,sizeof g);Count[0] = T + 1;
	int tmp = 0;
	while (D[S] < T + 1) tmp += dfs(S,1 << 30);
	return tmp;
}

class OldBridges
{
public:
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn)
	{
		N = bridges.size();
		memset(f,0,sizeof f);
		S = 0,T = N + 1;
		a1 ++,a2 ++,b1 ++,b2 ++;
		link(S,a1,2 * an);link(S,b1,2 * bn);
		for(int i = 1;i <= N;i ++)
		{
			for(int j = 1;j <= N;j ++)
			{
				char c = bridges[i - 1][j - 1];
				if (i > j) continue;
				if (c == 'O') link(i,j,2); else if (c == 'N') link(i,j,1 << 30);
			}
		}
		link(a2,T,2 * an);link(b2,T,2 * bn);
		if (maxflow() != 2 * (an + bn)) return "No"; else //假如第一次网络流就不合法那么显然不合法
		{
			f[S][a1] = 0;f[a2][T] = 0;f[S][a2] = 2 * an;f[a1][T] = 2 * an;//随便交换一对端点再跑一次
			if (maxflow() != 2 * (an + bn)) return "No"; else return "Yes";
		}
	}
};
