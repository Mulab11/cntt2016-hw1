#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

#define IL inline
#define RG register
#define dmin(a, b) ((a) < (b) ? (a) : (b))
struct Graph
{
	static const int MaxN = 10010, MaxM = 100010;
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
		*++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, 0, fir[b]}, fir[b] = tot;
		fir[a]->rev = fir[b];
		fir[b]->rev = fir[a];
	}
	IL void link(RG int a, RG int b, RG int f)
	{
		*++tot = (Pointer) {b, f, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, f, fir[b]}, fir[b] = tot;
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

int pid[60][60];

class FoxAndGo3
{
public:
	int maxEmptyCells(vector<string> map)
	{
		// 构建最小割
		// S 向所有“潜在黑点”连，所有白点向 T 连
		// 割表示保留，那么一个白点如果全割掉了黑点，就不用向 T 连啦
		int n = map.size(), m = map[0].size();
		int N = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(map[i - 1][j - 1] != 'x')
					pid[i][j] = ++N;
		G.init(N + 2, N + 1, N + 2);
		static int cx[] = {1, -1, 0, 0};
		static int cy[] = {0, 0, 1, -1};
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				char w = map[i - 1][j - 1];
				if(w == 'x') continue;
				else if(w == 'o')
				{
					G.add(pid[i][j], G.T, 1);
					for(int k = 0; k != 4; ++k)
					{
						int x = i + cx[k], y = j + cy[k];
						if(!pid[x][y]) continue;
						G.add(pid[x][y], pid[i][j], 1e9);
					}
				}
				else G.add(G.S, pid[i][j], 1);
			}
		return N - G.solve();
	}
}   user;
