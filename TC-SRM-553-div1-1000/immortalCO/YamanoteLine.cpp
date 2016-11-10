#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

int N;
ll M;
struct Line
{
	ll k, b;
	Line operator + (const Line& l) const {return (Line) {k + l.k, b + l.b};}
	Line operator - (const Line& l) const {return (Line) {k - l.k, b - l.b};}
	operator ll () {return k * M + b;}
};
struct Edge
{
	int to; Line len;
};
vector<Edge> e[60];

Line __pig_fail_record;
Line d[60];
bool v[60];

bool dfs(int p)
{
	v[p] = 1;
	const Line D = d[p];
	for(int k = (int) e[p].size(); k--; )
	{
		const int q = e[p][k].to;
		if(ll(D + e[p][k].len - d[q]) < 0)
		{
			if(v[q])
			{
				__pig_fail_record = D + e[p][k].len - d[q];
				return 1;
			}
			d[q] = D + e[p][k].len;
			if(dfs(q)) return 1;
		}
	}
	return (v[p] = 0);
}

int pig()
{
	// 返回值：
	// &1：是否失败
	// &2：是否有 k 为正的负权环
	// &4：是否有 k 为负的负权环
	memset(v, 0, (N + 1));
	memset(d, 0, (N + 1) << 4);
	for(int i = 0; i <= N; ++i) if(dfs(i))
	{
		int ret = 1;
		if(__pig_fail_record.k > 0) ret |= 2;
		if(__pig_fail_record.k < 0) ret |= 4;
		return ret;
	}
	return 0;
}

class YamanoteLine
{
public:
	ll howMany(int N, vector<int> a, vector<int> b, vector<int> c, vector<int> d, vector<int> f, vector<int> g)
	{
		::N = N;
		// 用包含 M（总长度） 的式子来加边
		// 每条边为正
		// x->y = v --> a[x] + v >= a[y]
		for(int i = 1; i <= N; ++i) e[i].push_back((Edge) {i - 1, (Line) {0ll, -1ll}});
		e[N].push_back((Edge) {0, (Line) {-1ll, 0ll}});
		e[0].push_back((Edge) {N, (Line) {+1ll, 0ll}});
		for(int i = 0; i != (int) a.size(); ++i)
		{
			const int s = a[i], t = b[i], v = c[i];
			if(s < t) 	e[t].push_back((Edge) {s, (Line) {0ll, (ll) -v}});
			else 		e[t].push_back((Edge) {s, (Line) {1ll, (ll) -v}});
		}
		for(int i = 0; i != (int) d.size(); ++i)
		{
			const int s = d[i], t = f[i], v = g[i];
			if(s < t)	e[s].push_back((Edge) {t, (Line) {0ll, (ll) v}});
			else		e[s].push_back((Edge) {t, (Line) {-1ll, (ll) v}});
		}
		
		// 可以二分枚举总长度
		// 用差分约束判断是否有正/负权环
		const ll inf = 1ll << 55; ll l, r;
		l = N, r = inf; while(l != r) {M = (l + r + 0) >> 1; (pig() & 2) ? l = M + 1 : r = M;} M = l; if(pig() & 1) return 0; const ll S = l;
		l = N, r = inf; while(l != r) {M = (l + r + 1) >> 1; (pig() & 4) ? r = M - 1 : l = M;} M = l; if(pig() & 1) return 0; const ll T = r;
		return T == inf ? -1 : T - S + 1;
	}
}	user;
