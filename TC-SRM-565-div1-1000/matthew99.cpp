#line 5 "UnknownTree.cpp"
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

const int Mod = 1e9 + 9;

const int maxn = 50;

int n;

vector<int> a, b, c;

inline int work3(vector<int> &dis)
{
	sort(ALL(dis));
	int n = SZ(dis);
	if (dis[0]) return 0;
	int j = 0;
	int ret = 1;
	REP(i, 1, n)
	{
		while (dis[j] < dis[i]) ++j;
		ret = (LL)ret * j % Mod;
		if (!ret) return 0;
	}
	return ret;
}

inline int work2(vector<int> &a, vector<int> &b, vector<int> &c, const int &db, const int &dc)
{
	if (!db || !dc) return 0;
	map<int, vector<int> > tob, toc;
	vector<int> suba;
	tob[db].pb(0);
	tob[-db].pb(0);
	toc[-dc].pb(0);
	REP(i, 0, n)
	{
		int u = b[i] - a[i], v = c[i] - a[i];
		if (v == dc) { if ((a[i] ^ b[i] ^ db) & 1) return 0; tob[u].pb((a[i] + b[i] - db) >> 1); }
		else if (u == db) { if ((a[i] ^ c[i] ^ dc) & 1) return 0; toc[v].pb((a[i] + c[i] - dc) >> 1); }
		else return 0;
	}
	int ret = 1;
	for (auto x : tob) { if (x.x < -db || x.x > db || ((x.x ^ db) & 1)) return 0; ret = (LL)ret * work3(x.y) % Mod; if (!ret) return 0; }
	for (auto x : toc) { if (x.x < -dc || x.x > dc || ((x.x ^ dc) & 1)) return 0; ret = (LL)ret * work3(x.y) % Mod; if (!ret) return 0; }
	return ret;
}

inline int work0(vector<int> &a, vector<int> &b, vector<int> &c)
{
	int p = min_element(ALL(a)) - a.begin();
	int u[2] = {a[p] + b[p], abs(a[p] - b[p])};
	int v[2] = {a[p] + c[p], abs(a[p] - c[p])};
	int ret = 0;
	REP(i, 0, 2) REP(j, 0, 2) (ret += work2(a, b, c, u[i], v[j])) %= Mod;
	return ret;
}

inline int work1(int x)
{
	int da = a[x], db = b[x], dc = c[x];
	map<int, vector<int> > toa, tob, toc;
	toa[-da - db].pb(0);
	tob[-db - dc].pb(0);
	toc[-dc - da].pb(0);
	REP(i, 0, n)
	{
		int u = a[i] - b[i], v = b[i] - c[i], w = c[i] - a[i];
		if (u == da - db) { if ((a[i] ^ c[i] ^ da ^ dc) & 1) return 0; toc[w].pb((a[i] + c[i] - da - dc) >> 1); }
		else if (v == db - dc) { if ((a[i] ^ b[i] ^ da ^ db) & 1) return 0; toa[u].pb((a[i] + b[i] - da - db) >> 1); }
		else if (w == dc - da) { if ((b[i] ^ c[i] ^ db ^ dc) & 1) return 0; tob[v].pb((b[i] + c[i] - db - dc) >> 1); }
		else return 0;
	}
	int ret = 1;
	for (auto x : toa) { if (x.x < -da - db || x.x > da - db || ((x.x ^ da ^ db) & 1)) return 0; ret = (LL)ret * work3(x.y) % Mod; if (!ret) return 0; }
	for (auto x : tob) { if (x.x < -db - dc || x.x > db - dc || ((x.x ^ db ^ dc) & 1)) return 0; ret = (LL)ret * work3(x.y) % Mod; if (!ret) return 0; }
	for (auto x : toc) { if (x.x < -dc - da || x.x > dc - da || ((x.x ^ dc ^ da) & 1)) return 0; ret = (LL)ret * work3(x.y) % Mod; if (!ret) return 0; }
	return ret;
}

class UnknownTree
{
	public:
		int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC)
		{
			a = distancesA;
			n = SZ(a);
			b = distancesB;
			c = distancesC;
			int ans = ((LL)work0(a, b, c) + work0(b, a, c) + work0(c, a, b)) % Mod;
			REP(i, 0, n) (ans += work1(i)) %= Mod;
			(ans += Mod) %= Mod;
			return ans;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
