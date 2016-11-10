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
	static const int MaxN = 30010, MaxM = 200010;
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

const int mov = 1e6;
const int inf = 1e9;

int p[60][60];
int dsqr(int x) {return x * x;}

class FoxAndCity
{
public:
	int minimalCost(vector<string> inp, vector<int> want)
	{
		// 通过操纵距离编号达到理想
		// 边 (x,y) -> d[x] + 1 >= d[y] && d[y] + 1 >= d[x]
		// 和 0 相连的点的距离必须是 1
		G.tot = G.mem;
		G.S = ++G.n;
		G.T = ++G.n;
		const int N = inp.size();
		for(int i = 1; i != N; ++i)
		{
			const int W = want[i];
			for(int j = 1; j <= N; ++j) p[i][j] = ++G.n;
			G.add(G.S, p[i][1], inf);
			G.add(p[i][N], G.T, inf);
			if(inp[0][i] == 'Y') // 距离必须是 1
			{
				G.add(p[i][1], p[i][2], dsqr(W - 1) + mov);
				for(int j = 2; j != N; ++j)
					G.add(p[i][j], p[i][j + 1], inf);
			}
			else for(int j = 1; j != N; ++j)
				G.add(p[i][j], p[i][j + 1], dsqr(W - j) + mov);
		}
		// 边的考虑
		for(int i = 1; i != N; ++i)
			for(int j = i + 1; j != N; ++j) if(inp[i][j] == 'Y')
			{
				// 距离之差必须小于 1
				for(int k = 2; k != N; ++k)
				{
					G.add(p[i][k], p[j][k - 1], inf);
					G.add(p[j][k], p[i][k - 1], inf);
				}
			}
		return G.solve() - (N - 1) * mov;
	}
}	user;
