#include <bits/stdc++.h>
using namespace std;
#define IL inline
#define RG register
#define dmin(a, b) ((a) < (b) ? (a) : (b))
struct Graph
{
	static const int MaxN = 4010, MaxM = 100010;
	struct Pointer{int to, flow; Pointer *next, *rev;} *fir[MaxN], *cur[MaxN];
	Pointer mem[MaxM << 1], *tot;
	int n, S, T;
	IL void init(RG int _n, RG int _S, RG int _T)
	{
		n = _n, S = _S, T = _T;
		tot = mem;
		memset(fir + 1, 0, n * sizeof fir[0]);
	}
	IL void add(RG int a, RG int b, RG int f, RG int r = 0)
	{
		if(!a || !b) return;
		*++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, r, fir[b]}, fir[b] = tot;
		fir[a]->rev = fir[b];
		fir[b]->rev = fir[a];
	}
	int dist[MaxN];
	IL bool bfs()
	{
		static int q[MaxN];
		RG int l = 1, r = 0, d;
		RG Pointer *k;
		memset(dist + 1, 0, n << 2);
		dist[q[++r] = T] = 1;
		while(l <= r)
		{
			d = dist[q[l]] + 1;
			for(k = fir[q[l++]]; k; k = k->next)
			{
				if(k->rev->flow && !dist[k->to])
					dist[q[++r] = k->to] = d;
			}
		}
		return dist[S];
	}
	int dfs(RG int i, RG int lim)
	{
		if(i == T || !lim) return lim;
		RG int want = dist[i] - 1;
		RG int used = 0, temp;
		for(RG Pointer* &k = cur[i]; k; k = k->next)
			if(dist[k->to] == want && k->flow)
			{
				temp = dfs(k->to, dmin(lim - used, k->flow));
				used += temp;
				k->flow -= temp;
				k->rev->flow += temp;
				if(used == lim) break;
			}
		return used;
	}
	IL int solve()
	{
		RG int ans = 0;
		while(bfs())
		{
			memcpy(cur + 1, fir + 1, n * sizeof *fir);
			ans += dfs(S, 1 << 30);
		}
		return ans;
	}
} G;
class SurroundingGame
{
	int decode(int w)
	{
		if('0' <= w && w <= '9') return 0 + w - '0';
		if('a' <= w && w <= 'z') return 10 + w - 'a';
		if('A' <= w && w <= 'Z') return 36 + w - 'A';
		return -1;
	}
	static const int MaxN = 25;
	int P[MaxN][MaxN], Q[MaxN][MaxN], C[MaxN][MaxN], V[MaxN][MaxN];
public:
	int maxScore(vector<string> argv1, vector<string> argv2)
	{
		const int mov = 100000;
		const int N = argv1.size(), M = argv1.front().size();
		assert((int) argv2.size() == N && (int) argv2.front().size() == M);
		int NP = 0, ans_mov = mov * N * M;
		for(int i = 1; i <= N; ++i) for(int j = 1; j <= M; ++j)
			P[i][j] = ++NP,
			Q[i][j] = ++NP,
			C[i][j] = decode(argv1[i - 1][j - 1]),
			V[i][j] = decode(argv2[i - 1][j - 1]),
			ans_mov += V[i][j];
		G.init(NP + 2, NP + 1, NP + 2);
		
		int X[] = {1, -1, 0, 0};
		int Y[] = {0, 0, 1, -1};
		for(int i = 1; i <= N; ++i) for(int j = 1; j <= M; ++j)
		{
			if((i + j) % 2 == 0)
			{
				G.add(G.S, P[i][j], mov + 0000000);
				G.add(P[i][j], G.T, mov + C[i][j]);
				G.add(Q[i][j], P[i][j], V[i][j]);
				for(int k = 0; k != 4; ++k)
					G.add(P[i + X[k]][j + Y[k]], Q[i][j], 1000000000);
			}
			else
			{
				G.add(G.S, P[i][j], mov + C[i][j]);
				G.add(P[i][j], G.T, mov + 0000000);
				G.add(P[i][j], Q[i][j], V[i][j]);
				for(int k = 0; k != 4; ++k)
					G.add(Q[i][j], P[i + X[k]][j + Y[k]], 1000000000);
			}
		}
		return ans_mov - G.solve();
	}
}	user;