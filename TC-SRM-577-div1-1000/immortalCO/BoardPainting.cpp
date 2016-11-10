#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;


struct Graph
{
#define IL inline
#define RG register
#define dmin(a, b) ((a) < (b) ? (a) : (b))
	static const int MaxN = 100000, MaxM = 200000;
	struct Pointer{int to, flow; Pointer *next, *rev;} *fir[MaxN], *cur[MaxN];
	Pointer mem[MaxM << 1], *tot;
	int n, S, T;
	IL void init(RG int _n, RG int _S, RG int _T)
	{
		n = _n, S = _S, T = _T;
		tot = mem;
		memset(fir + 1, 0, n * sizeof fir[0]);
	}
	IL void add(RG int a, RG int b, RG int f)
	{
		if(!a || !b || !f) return;
		*++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, 0, fir[b]}, fir[b] = tot;
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

bool map[60][60];
int H[60][60], V[60][60];	// 水平和竖直的边

class BoardPainting
{
public:
	int minimalSteps(vector<string> inp)
	{
		// 选择一条边意味着少一次操作
		// 水平和竖直的边不能同时选择，这是二分图最大独立集
		G.tot = G.mem;
		G.S = ++G.n;
		G.T = ++G.n;
		int N = inp.size(), M = inp[0].size();
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				map[i][j] = (inp[i - 1][j - 1] == '#');
		int A = 0;
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				if(map[i][j])
				{
					++A;
					if(map[i][j + 1]) G.add(G.S, H[i][j] = ++G.n, 1);
					if(map[i + 1][j]) G.add(V[i][j] = ++G.n, G.T, 1);
				}
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
			{
				G.add(H[i][j - 1], V[i - 1][j], 1 << 30);
				G.add(H[i][j - 1], V[i - 0][j], 1 << 30);
				G.add(H[i][j - 0], V[i - 1][j], 1 << 30);
				G.add(H[i][j - 0], V[i - 0][j], 1 << 30);
			}
		return A - (G.n - 2 - G.solve());
	}
}	user;
