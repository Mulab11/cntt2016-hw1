#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

// 贴个费用流的板子
namespace G
{
#define IL inline
#define RG register
	const int MaxN = 10010;
	const int MaxM = 500010;
	
	struct Pointer
	{
		int to, flow, cost; Pointer *next, *rev;
		IL void use(RG int x) {flow -= x; rev->flow += x;}
	};
	Pointer *fir[MaxN], mem[MaxM], *tot = mem;
	IL void add(RG int a, RG int b, RG int f, RG int c)
	{
		*++tot = (Pointer) {b, f, c, fir[a]}, fir[a] = tot;
		*++tot = (Pointer) {a, 0, -c, fir[b]}, fir[b] = tot;
		fir[a]->rev = fir[b];
		fir[b]->rev = fir[a];
	}
	
	int n, S, T;
	int flow[MaxN];
	ll dist[MaxN];
	Pointer *from[MaxN];
	bool in[MaxN];
	int q[MaxN << 3];
	
	IL bool spfa()
	{
		RG int l = 0, r = 0;
		memset(dist + 1, 63, n << 3);
		in[q[r++] = S] = 1;
		flow[S] = 1 << 30;
		dist[S] = 0;
		while(l != r)
		{
			RG int p = q[l++], F = flow[p];
			RG ll D = dist[p];
			in[p] = 0;
			for(RG Pointer *k = fir[p]; k; k = k->next)
				if(k->flow && D + k->cost < dist[k->to])
				{
					dist[k->to] = D + k->cost;
					flow[k->to] = min(F, k->flow);
					from[k->to] = k;
					if(!in[k->to]) in[q[r++] = k->to] = 1;
				}
		}
		return dist[T] <= (1ll << 50);
	}
	IL pair<int, ll> solve()
	{
		RG ll ans = 0;
		RG int sum = 0;
		while(spfa())
		{
			ans += dist[T];
			RG int Flow = flow[T];
			sum += Flow;
			for(RG int p = T; p != S; p = from[p]->rev->to)
				from[p]->use(Flow);
		}
		return make_pair(sum, ans);
	}
}

int map[30][30];
int point[30][30], edge[30][30][2];

class CurvyonRails
{
public:
	int getmin(vector<string> inp)
	{
		int n = inp.size(), m = inp[0].size();
		G::S = ++G::n;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				if(inp[i - 1][j - 1] == '.') map[i][j] = -1;
				else if(inp[i - 1][j - 1] == 'C') map[i][j] = 1;
				if(map[i][j])
				{
					point[i][j] = ++G::n;
					edge[i][j][0] = ++G::n;
					edge[i][j][1] = ++G::n;
				}
			}
		G::T = ++G::n;
		int Left = 0, Right = 0;
		const int X[] = {1, -1, 0, 0};
		const int Y[] = {0, 0, 1, -1};
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
				if(map[i][j])
				{
					if((i + j) & 1)
					{
						++Left;
						G::add(G::S, point[i][j], 2, 0);
						G::add(point[i][j], edge[i][j][0], 1, 0);
						G::add(point[i][j], edge[i][j][0], 1, (map[i][j] == 1));
						G::add(point[i][j], edge[i][j][1], 1, 0);
						G::add(point[i][j], edge[i][j][1], 1, (map[i][j] == 1));
						for(int k = 0; k != 4; ++k)
						{
							int x = i + X[k], y = j + Y[k];
							if(!map[x][y]) continue;
							G::add(edge[i][j][k < 2], edge[x][y][k < 2], 1, 0);
						}
					}
					else
					{
						++Right;
						G::add(edge[i][j][0], point[i][j], 1, 0);
						G::add(edge[i][j][0], point[i][j], 1, (map[i][j] == 1));
						G::add(edge[i][j][1], point[i][j], 1, 0);
						G::add(edge[i][j][1], point[i][j], 1, (map[i][j] == 1));
						G::add(point[i][j], G::T, 2, 0);
					}
				}
		if(Left != Right) return -1;
		pair<int, ll> ret = G::solve();
		if(ret.first != Left + Right) return -1;
		return ret.second;
		
	}
}	user;
