#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MaxN = 60;
int Hash[MaxN], A[MaxN][MaxN], B[MaxN][MaxN];

// 其实就是最短路啦
// 贴个费用流的板子
namespace G
{
#define IL inline
#define RG register
	const int MaxN = 5010;
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
	IL ll solve()
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
		return sum ? ans : -1;
	}
}

class SkiResorts
{
public:
	ll minCost(vector<string> road, vector<int> phi)
	{
		// 其实就是最短路啦
		// 直接贴一个费用流的板子
		int n = phi.size();
		for(int i = 0; i != n; ++i) Hash[i] = phi[i];
		sort(Hash, Hash + n);
		int h = unique(Hash, Hash + n) - Hash;
		G::S = ++G::n;
		for(int i = 0; i != n; ++i)
		{
			int H = phi[i];
			for(int j = 0; j != h; ++j)
			{
				A[i][j] = ++G::n;
				B[i][j] = ++G::n;
				G::add(A[i][j], B[i][j], 1, max(H - Hash[j], Hash[j] - H));
				if(j) G::add(B[i][j], B[i][j - 1], 1, 0);
			}
		}
		++G::n;
		G::T = ++G::n;
		for(int j = 0; j != h; ++j)
		{
			G::add(G::S, A[0][j], 1, 0);
			G::add(B[n - 1][j], G::n - 1, 1, 0);
		}
		G::add(G::n - 1, G::T, 1, 0);
		for(int i = 0; i != n; ++i)
			for(int j = 0; j != n; ++j)
				if(road[i][j] == 'Y')
					for(int k = 0; k != h; ++k)
						G::add(B[i][k], A[j][k], 1, 0);
		return G::solve();
	}
}   user;
