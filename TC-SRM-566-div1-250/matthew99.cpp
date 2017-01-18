#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
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

int m;

bool g[maxn + 5][maxn + 5];

class PenguinSledding 
{
	public:
		long long countDesigns(int n, vector<int> u, vector<int> v) 
		{
			memset(g, 0, sizeof g);
			m = SZ(u);
			REP(i, 0, m) --u[i], --v[i], g[u[i]][v[i]] = g[v[i]][u[i]] = 1;
			LL ret = 1;
			REP(i, 0, n) REP(j, 0, i) if (g[i][j]) 
			{
				++ret;
				REP(k, 0, j) if (g[k][i] && g[k][j]) ++ret;
			}
			REP(i, 0, n)
			{
				int cnt = 0;
				REP(j, 0, n) if (g[i][j]) ++cnt;
				if (cnt >= 2) ret += (1LL << cnt) - cnt - 1;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
