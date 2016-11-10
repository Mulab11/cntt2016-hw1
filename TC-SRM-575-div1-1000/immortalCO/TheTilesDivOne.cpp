#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

#define IL inline
#define RG register
#define dmin(a, b) ((a) < (b) ? (a) : (b))
struct Graph
{
	static const int MaxN = 20010, MaxM = 100010;
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

bool map[55][55];
int bp[55][55][2], wp[55][55];

class TheTilesDivOne
{
public:
	int find(vector<string> inp)
	{
		const int N = inp.size(), M = inp[0].size();
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				(map[i][j] = inp[i - 1][j - 1] == '.');
		G.tot = G.mem;
		G.S = ++G.n;
		G.T = ++G.n;
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				if(map[i][j])
				{
					if((i + j) % 2)
					{
						wp[i][j] = ++G.n;
						if(i % 2)	G.add(G.S, wp[i][j], 1);
						else		G.add(wp[i][j], G.T, 1);
					}
					else
					{
						bp[i][j][0] = ++G.n;
						bp[i][j][1] = ++G.n;
						G.add(bp[i][j][0], bp[i][j][1], 1);
					}
				}
		const int X[] = {1, -1, 0, 0};
		const int Y[] = {0, 0, 1, -1};
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= M; ++j)
				if(map[i][j] && (i + j) % 2 == 0)
					for(int k = 0; k != 4; ++k)
					{
						int x = i + X[k];
						int y = j + Y[k];
						if(!map[x][y]) continue;
						if(x % 2) 	G.add(wp[x][y], bp[i][j][0], 1);
						else		G.add(bp[i][j][1], wp[x][y], 1);
					}
		return G.solve();
		
	}
}	user;
