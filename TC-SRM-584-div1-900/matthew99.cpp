#line 5 "FoxTheLinguist.cpp"
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

const int maxn = 100;

struct Edge
{
	int x, y, z;

	Edge() { }
	Edge(int _x, int _y, int _z): x(_x), y(_y), z(_z) { }

};

int m;
vector<Edge> ed;

int fa[maxn + 5];
int Min[maxn + 5];

int pre[maxn + 5], prep[maxn + 5];

int get(int x) { return fa[x] == x ? x : fa[x] = get(fa[x]); }

class FoxTheLinguist
{
	public:
		int minimalHours(int n, vector <string> courseInfo)
		{
			ed.clear();
			REP(i, 0, n) ed.pb(Edge(n * 10, i * 10, 0));
			REP(i, 0, n) REP(j, 1, 10) ed.pb(Edge(i * 10 + j, i * 10 + j - 1, 0));
			stringstream in(accumulate(ALL(courseInfo), string("")));
			string tmp;
			while (in >> tmp)
			{
				char u0, v0;
				int u1, v1, val;
				sscanf(tmp.c_str(), "%c%d->%c%d:%d", &u0, &u1, &v0, &v1, &val);
				ed.pb(Edge((u0 - 'A') * 10 + u1, (v0 - 'A') * 10 + v1, val));
			}
			n *= 10;
			m = SZ(ed);
			memset(pre, 0, sizeof pre);
			memset(prep, -1, sizeof prep);
			REP(i, 0, n + 1) fa[i] = i;
			int ans = 0;
			while (1)
			{
				memset(Min, -1, sizeof Min);
				REP(i, 0, m)
				{
					int x = ed[i].x, y = ed[i].y;
					if (x != y)
						if (!~Min[y] || ed[Min[y]].z - pre[ed[Min[y]].y] > ed[i].z - pre[ed[i].y]) Min[y] = i;
				}
				REP(i, 0, n) if (fa[i] == i)
				{
					if (!~Min[i]) return -1;
					int x = ed[Min[i]].x, y = ed[Min[i]].y, z = ed[Min[i]].z;
					ans += z;
					prep[y] = x;
					pre[y] = z;
				}
				static int vis[maxn + 5];
				bool flag = 0;
				memset(vis, -1, sizeof vis);
				REP(i, 0, n) if (fa[i])
				{
					int u = i;
					while (~u)
					{
						if (~vis[u]) break;
						vis[u] = i;
						u = prep[u];
					}
					if (~u && vis[u] == i)
					{
						flag = 1;
						int v = u;
						do
						{
							fa[get(v)] = get(u);
							v = prep[v];
						}while (v != u);
					}
				}
				if (!flag) break;
				REP(i, 0, m) 
				{
					ed[i].z -= pre[ed[i].y];
					ed[i].x = get(ed[i].x), ed[i].y = get(ed[i].y);
				}
			}
			return ans;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
