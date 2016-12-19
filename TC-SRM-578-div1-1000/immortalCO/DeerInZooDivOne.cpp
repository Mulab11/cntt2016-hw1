#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

const int MaxN = 55;

namespace G
{
#define IL inline
#define RG register
	const int MaxN = 210;
	const int MaxM = 10010;
	
	struct Pointer
	{
		int to, flow, cost; Pointer *next, *rev;
		IL void use(RG int x) {flow -= x; rev->flow += x;}
	};
	Pointer *fir[MaxN], mem[MaxM], *tot;
	IL void add(RG int a, RG int b, RG int f, RG int c)
	{
		*++tot = (Pointer) {b, f, c, fir[a], 0}, fir[a] = tot;
		*++tot = (Pointer) {a, 0, -c, fir[b], 0}, fir[b] = tot;
		fir[a]->rev = fir[b];
		fir[b]->rev = fir[a];
	}
	
	int n, S, T;
	int flow[MaxN];
	int dist[MaxN];
	Pointer *from[MaxN];
	bool in[MaxN];
	int q[MaxN << 3];
	IL void init(int _n, int _S, int _T)
	{
		n = _n, S = _S, T = _T;
		tot = mem;
		memset(fir + 1, 0, n * sizeof *fir);
	}
	
	IL bool spfa()
	{
		RG int l = 0, r = 0;
		memset(dist + 1, 63, n << 2);
		in[q[r++] = S] = 1;
		flow[S] = 1 << 30;
		dist[S] = 0;
		while(l != r)
		{
			RG int p = q[l++], F = flow[p];
			RG int D = dist[p];
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
		return dist[T] <= 1e9;
	}
	IL pair<int, int> solve()
	{
		RG int ans = 0;
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

struct Pointer
{
	int to; Pointer *next, *rev;
	bool vis;
	void set_vis(bool k) {vis = rev->vis = k;}
	void init(int i, Pointer *n) {to = i, next = n;}
} *fir[MaxN], mem[MaxN << 1], *tot = mem + 1;
void link(int a, int b)
{
	(++tot)->init(b, fir[a]), fir[a] = tot;
	(++tot)->init(a, fir[b]), fir[b] = tot;
	fir[a]->rev = fir[b];
	fir[b]->rev = fir[a];
}

int f[MaxN << 1][MaxN << 1], v[MaxN << 1][MaxN << 1], timer;
ll list;
void dfs_list(int i)
{
	list -= 1ll << i;
	for(Pointer *k = fir[i]; k; k = k->next)
		if(!k->vis)
		{
			k->set_vis(1);
			dfs_list(k->to);
			k->set_vis(0);
		}
}
int dp(Pointer *p, Pointer *q)
{
	if(q != mem && v[p - mem][q - mem] == timer)
		return f[p - mem][q - mem];
	v[p - mem][q - mem] = timer;
	int &ret = f[p - mem][q - mem];
	// 考虑实现一个匹配
	vector<Pointer*> pkv, qkv;
	for(Pointer *pk = fir[p->to]; pk; pk = pk->next)
		if(!pk->vis && pk != p->rev)
		{
			pkv.push_back(pk);
		}
	for(Pointer *qk = fir[q->to]; qk; qk = qk->next)
		if(!qk->vis && qk != q->rev) qkv.push_back(qk);
	// 先递归下去做
	for(int pi = 0; pi != (int) pkv.size(); ++pi)
		for(int qi = 0; qi != (int) qkv.size(); ++qi)
			dp(pkv[pi], qkv[qi]);
	
	G::init(
			pkv.size() + qkv.size() + 2,
			pkv.size() + qkv.size() + 1,
			pkv.size() + qkv.size() + 2);
	const int pmov = 1, qmov = pkv.size() + 1;
	for(int pi = 0; pi != (int) pkv.size(); ++pi) G::add(G::S, pmov + pi, 1, 0);
	for(int qi = 0; qi != (int) qkv.size(); ++qi) G::add(qmov + qi, G::T, 1, 0);
	for(int pi = 0; pi != (int) pkv.size(); ++pi)
		for(int qi = 0; qi != (int) qkv.size(); ++qi)
		{
			// 用一个费用流去二分图匹配
			G::add(pmov + pi, qmov + qi, 1, -dp(pkv[pi], qkv[qi]));
		}
	ret = 1 - G::solve().second;
	return ret;
}

class DeerInZooDivOne
{
public:
	int getmax(vector<int> ea, vector<int> eb)
	{
		const int N = ea.size() + 1;
		for(int i = 0; i != N - 1; ++i) link(ea[i], eb[i]);
		int ans = 1;
		// 枚举切断哪一条边，并且某个连通块一定包含这条边的出点
		mem->rev = mem;
		for(Pointer *e = mem + 2; e <= tot; ++e)
		{
			++timer;
			e->set_vis(1);
			// 处理出列表
			list = (1ll << N) - 1;
			dfs_list(e->to);
			if(min(__builtin_popcountll(list), N - __builtin_popcountll(list)) > ans)
			{
				// 枚举对应点
				for(int i = 0; i != N; ++i) if(1ll << i & list)
				{
					mem->to = i;
					ans = max(ans, dp(e, mem));
				}
			}
			e->set_vis(0);
		}
		return ans;
	}
}	user;
