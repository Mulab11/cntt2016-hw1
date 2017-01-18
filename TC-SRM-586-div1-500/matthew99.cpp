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

const int maxn = 30;

int n;
int f[maxn + 5][maxn + 5];
int g[maxn + 5][maxn + 5];

vector<int> all[maxn + 5];

inline void add_lim(int u, int x, int v, int y, int g[maxn + 5][maxn + 5])
{
	//dis[u] + all[u][x] < dis[v] + all[v][y + 1]
	//dis[u] + all[u][x] <= dis[v] + all[v][y + 1] - 1
	//dis[u] <= dis[v] + all[v][y + 1] - all[u][x] - 1
	chkmin(g[v][u], all[v][y + 1] - all[u][x] - 1);
}

inline void add(const string &s, int g[maxn + 5][maxn + 5])
{
	char a, b;
	int u, v;
	int x, y;
	sscanf(s.c_str(), "%c%d-%c%d", &a, &x, &b, &y);
	u = a - 'A', v = b - 'A';
	add_lim(u, x, v, y, g);
	add_lim(v, y, u, x, g);
}

class History 
{
	public:
		string verifyClaims(vector<string> dynasties, vector<string> battles, vector<string> queries) 
		{
			n = 0;
			for (auto x : dynasties)
			{
				istringstream in(x);
				int tmp;
				all[n].clear();
				while (in >> tmp) all[n].pb(tmp);
				++n;
			}
			memset(g, oo, sizeof g);
			REP(i, 0, n) g[i][i] = 0;
			for (auto x : battles)
			{
				istringstream in(accumulate(ALL(battles), string("")));
				string s;
				while (in >> s) add(s, g);
			}
			string ret;
			for (auto x : queries)
			{
				memcpy(f, g, sizeof f);
				add(x, f);
				bool ok = 1;
				REP(k, 0, n) 
				{
					REP(i, 0, n) REP(j, 0, n) if (f[i][k] < oo && f[k][j] < oo) chkmin(f[i][j], f[i][k] + f[k][j]);
					REP(i, 0, n) if (f[i][i] < 0) { ok = 0; break; }
					if (!ok) break;
				}
				ret.pb(ok ? 'Y' : 'N');
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
