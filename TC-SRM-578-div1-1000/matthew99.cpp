#line 5 "DeerInZooDivOne.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

const int maxn = 60;

int n;
vector<int> adj[maxn + 5];

map<int, int> dp;

namespace KM
{
	const int max0 = 1000;

	int v[max0 + 5][max0 + 5];

	int cnt[2];

	int slack[max0 + 5];

	int wx[max0 + 5], wy[max0 + 5];
	int linkx[max0 + 5], linky[max0 + 5];
	int pre[max0 + 5];
	bool visx[max0 + 5], visy[max0 + 5];

	int q[max0 + 5];
	int head = 0, rear = 0;

	int bfs()
	{
		while (head != rear)
		{
			const int &x = q[head++];
			REP(y, 0, cnt[0] + cnt[1])
			{
				if (visy[y] || v[x][y] == -1) continue;
				int tmp = wx[x] + wy[y] - v[x][y];
				if (!tmp)
				{
					pre[y] = x;
					if (linky[y] == -1) return y;
					visy[y] = 1;
					if (!visx[linky[y]]) visx[linky[y]] = 1, q[rear++] = linky[y];
				}
				else if (tmp < slack[y]) slack[y] = tmp, pre[y] = x;
			}
		}
		int delta = oo;
		REP(i, 0, cnt[0] + cnt[1]) if (!visy[i]) delta = min(delta, slack[i]);
		REP(i, 0, cnt[0]) if (visx[i]) wx[i] -= delta;
		REP(i, 0, cnt[0] + cnt[1])
			if (visy[i]) wy[i] += delta;
			else if (slack[i] < oo) slack[i] -= delta;
		REP(i, 0, cnt[0] + cnt[1])		
			if (!visy[i] && !slack[i])
			{
				int &y = i;
				if (linky[y] == -1) return y;
				visy[y] = 1;
				if (!visx[linky[y]]) visx[linky[y]] = 1, q[rear++] = linky[y];
			}
		return -1;
	}

	int work()
	{
		REP(i, 0, cnt[0])
		{
			wx[i] = 0;
			REP(j, 0, cnt[0] + cnt[1])
				wx[i] = max(wx[i], v[i][j]);
		}
		memset(wy, 0, sizeof(wy[0]) * (cnt[0] + cnt[1]));
		memset(linkx, -1, sizeof(linkx[0]) * (cnt[0] + cnt[1]));
		memset(linky, -1, sizeof(linky[0]) * (cnt[0] + cnt[1]));
		REP(i, 0, cnt[0])
		{
			memset(visx, 0, sizeof(visy[0]) * (cnt[0] + cnt[1]));
			memset(visy, 0, sizeof(visy[0]) * (cnt[0] + cnt[1]));
			memset(slack, oo, sizeof(slack[0]) * (cnt[0] + cnt[1]));
			memset(pre, -1, sizeof(pre[0]) * (cnt[0] + cnt[1]));
			head = rear = 0;
			visx[q[rear++] = i] = 1;
			int u = -1;
			while ((u = bfs()) == -1);
			while (u != -1)
			{
				int tmp = linkx[pre[u]];
				linkx[linky[u] = pre[u]] = u;
				u = tmp;
			}
		}
		int ret = 0;
		REP(i, 0, cnt[0]) ret += wx[i];
		REP(i, 0, cnt[0] + cnt[1]) ret += wy[i]; 
		return ret;
	}

	int work(int X, int Y, const vector<pair<pair<int, int>, int> > &ed)
	{
		cnt[0] = X, cnt[1] = Y;
		REP(i, 0, cnt[0] + cnt[1]) REP(j, 0, cnt[0] + cnt[1]) v[i][j] = -1;
		REP(i, 0, cnt[0]) REP(j, cnt[1], cnt[1] + cnt[0]) v[i][j] = 0;
		for (auto x : ed) v[x.x.x][x.x.y] = x.y;
		return work();
	}

}

inline int get(int a, int b, int c, int d)
{
	if (mp(a, b) < mp(c, d)) swap(a, c), swap(b, d);
	int tmp = ((a * (n + 1) + b) * (n + 1) + c) * (n + 1) + d;
	if (dp.count(tmp)) return dp[tmp];
	int &ret = dp[tmp];
	vector<int> u, v;
	for (auto x : adj[a]) if (x != b) u.pb(x);
	for (auto x : adj[c]) if (x != d) v.pb(x);
	vector<pair<pair<int, int>, int> > ed;
	REP(i, 0, SZ(u)) REP(j, 0, SZ(v)) ed.pb(mp(mp(i, j), get(u[i], a, v[j], c)));
	ret = 1 + KM::work(SZ(u), SZ(v), ed);
	return ret;
}

int fa[maxn + 5];
inline int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

class DeerInZooDivOne
{
	public:
		int getmax(vector <int> a, vector <int> b)
		{
			n = SZ(a) + 1;
			int ret = 0;
			REP(j, 0, n - 1)
			{
				REP(i, 0, n) adj[i].clear(), fa[i] = i;
				REP(i, 0, n - 1) if (j != i) adj[a[i]].pb(b[i]), adj[b[i]].pb(a[i]), fa[get(a[i])] = get(b[i]);
				dp.clear();
				REP(i, 0, n) REP(j, 0, i) if (get(i) != get(j)) chkmax(ret, get(i, n, j, n));
			}
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
