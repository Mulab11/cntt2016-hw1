#line 5 "FoxAndCity.cpp"
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

const int max0 = 100000, max1 = 1000000;
 
struct edge
{
	int id, g, nxt;
 
	edge() { }
	edge(int _id, int _g, int _nxt): id(_id), g(_g), nxt(_nxt) { }
 
};
 
int st[max0 + 5], en = 0;
edge e[max1 + 5];
 
inline void add_edge(int x, int y, int z)
{
	e[en] = edge(y, z, st[x]), st[x] = en++;
}

inline void add_biedge(int x, int y, int z) { add_edge(x, y, z), add_edge(y, x, 0); }
 
int S, T, N;

int dis[max0 + 5];
 
inline bool bfs()
{
	static int q[max0 + 5];
	static bool vis[max0 + 5];
	int head = 0, rear = 0;
	memset(dis, -1, sizeof(dis[0]) * N);
	memset(vis, 0, sizeof(vis[0]) * N);
	vis[q[rear++] = S] = 1;
	dis[S] = 0;
	while (head != rear)
	{
		int x = q[head++];
		for (int i = st[x]; i != -1; i = e[i].nxt)
		{
			if (!e[i].g) continue;
			int y = e[i].id;
			if (!vis[y])
			{
				dis[y] = dis[x] + 1;
				if (y == T) return 1;
				q[rear++] = y;
				vis[y] = 1;
			}
		}
	}
	return 0;
}

int cur[max0 + 5];
 
inline int dfs(int x, int flow)
{
	if (x == T) return flow;
	int res = flow;
	for (int &i = cur[x]; i != -1; i = e[i].nxt)
	{
		if (!e[i].g) continue;
		int y = e[i].id;
		if (dis[y] == dis[x] + 1)
		{
			int F = dfs(y, min(e[i].g, res));
			res -= F;
			e[i].g -= F;
			e[i ^ 1].g += F;
			if (res <= 0) return flow;
		}
	}
	dis[x] = -1;
	return flow - res;
}
 
int work()
{
	if (S == T) return oo;
	int ret = 0;
	for ( ; bfs(); )
	{
		REP(i, 0, N) cur[i] = st[i];
		ret += dfs(S, oo);
	}
	return ret;
}

const int maxn = 50;

int n;

inline int calc(int x, int y) { return (x - y) * (x - y); }

class FoxAndCity
{
	public:
		int minimalCost(vector <string> linked, vector <int> want)
		{
			memset(st, -1, sizeof st), en = 0;
			n = SZ(linked);
			N = n * (n + 1) + 2;
			S = N - 2, T = N - 1;
			REP(i, 0, n) 
			{
				add_biedge(S, i * (n + 1), oo);
				if (!i) REP(j, 0, n) add_biedge(i * (n + 1) + j, i * (n + 1) + j + 1, (!j ? 0 : oo));
				else REP(j, 0, n) add_biedge(i * (n + 1) + j, i * (n + 1) + j + 1, (!j ? oo : calc(j, want[i])));
				add_biedge(i * (n + 1) + n, T, oo);
			}
			REP(i, 0, n) REP(j, 0, n) if (linked[i][j] == 'Y') REP(k, 0, n - 1) add_biedge(j * (n + 1) + k + 1, i * (n + 1) + k, oo);
			return work();
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
