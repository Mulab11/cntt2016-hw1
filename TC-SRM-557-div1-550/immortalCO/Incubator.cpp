#include <bits/stdc++.h>
using namespace std;

long long e[55];
struct Max_Flow_Graph
{
	static const int MaxN = 110;
	static const int MaxM = 10210;
	static const int inf = 2e9;
	struct Pointer{int to, flow; Pointer *next, *rev;};
	Pointer mem[MaxM << 1], *tot, *fir[MaxN];
	int n, S, T;
	void init(int _n, int _S, int _T)
	{
		n = _n, S = _S, T = _T;
		tot = mem;
		memset(fir + 1, 0, n * sizeof *fir);
	}
	void add(int a, int b, int f)
	{
		*++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, 0, fir[b]}, fir[b] = tot;
		fir[a]->rev = fir[b];
		fir[b]->rev = fir[a];
	}
	int dis[MaxN];
	Pointer *cur[MaxN];
	bool bfs()
	{
		static int q[MaxN]; int l = 0, r = 0;
		memset(dis + 1, 0, n << 2);
		dis[q[r++] = T] = 1;
		Pointer *k;
		for(int p, d; l != r; )
		{
			p = q[l++], d = dis[p] + 1;
			for(k = fir[p]; k; k = k->next)
				if(k->rev->flow && !dis[k->to])
					dis[q[r++] = k->to] = d;
		}
		return dis[S];
	}
	int dfs(int i, int Max)
	{
		if(i == T) return Max;
		int Use = 0, Tmp, D = dis[i] - 1;
		for(Pointer *&k = cur[i]; k; k = k->next)
			if(dis[k->to] == D && k->flow)
			{
				Tmp = dfs(k->to, min(k->flow, Max - Use));
				Use += Tmp;
				k->flow -= Tmp;
				k->rev->flow += Tmp;
				if(Use == Max) break;
			}
		return Use;
	}
	int solve()
	{
		int ans = 0;
		while(bfs())
		{
			memcpy(cur + 1, fir + 1, n * sizeof *fir);
			ans += dfs(S, inf);
		}
		return ans;
	}
}    G;

class Incubator
{
public:
	int maxMagicalGirls(vector<string> map)
	{
		int N = map.size();
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j)
				if(i == j || map[i-1][j-1] == 'Y')
					e[i] += 1ll << j;
		for(int k = 1; k <= N; ++k)
			for(int i = 1; i <= N; ++i)
				if(e[i] & (1ll << k))
					e[i] |= e[k];
		for(int i = 1; i <= N; ++i)
			if(map[i-1][i-1] == 'N')
				e[i] -= 1ll << i;
		G.init(N * 2 + 2, N * 2 + 1, N * 2 + 2);
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j)
				if(e[i] & (1ll << j))
					G.add(i, N + j, 1);
		for(int i = 1; i <= N; ++i)
			G.add(G.S, i, 1), G.add(N + i, G.T, 1);
		return N - G.solve();
	}
}	user;
