#line 5 "SimilarNames.cpp"
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

const int Mod = 1e9 + 7;

const int oo = 0x3f3f3f3f;

const int maxn = 50, maxm = 8;

int N;
int n, m;

pair<int, int> b[maxm + 5];

inline bool is_prefix(const string &a, const string &b) { return b.substr(0, SZ(a)) == a; }

inline bool cmp(const string &a, const string &b) { return SZ(a) < SZ(b); }

int fa[maxn + 5];
vector<int> adj[maxn + 5];

int id[maxn + 5];

int S;

int req[maxn + 5], ban[(1 << (maxm << 1)) + 5];
int dp[maxn + 5][(1 << (maxm << 1)) + 5];

void dfs(int x)
{
	static int tmp[(1 << (maxm << 1)) + 5];
	dp[x][0] = 1;
	for (auto y : adj[x])
	{
		dfs(y);
		memset(tmp, 0, sizeof tmp);
		REP(i, 0, 1 << N) if (dp[x][i]) for (int j = S ^ i; ; j = (j - 1) & (S ^ i)) if (dp[y][j])
		{
			if (ban[i] & j) continue;
			(tmp[i | j] += (LL)dp[x][i] * dp[y][j] % Mod) %= Mod;
			if (!j) break;
		}
		memcpy(dp[x], tmp, sizeof dp[x]);
	}
	if (x < n) for (int i = (1 << N) - 1; i >= 0; --i) if (dp[x][i]) REP(j, 0, N) if (!(i >> j & 1) && (req[j] & i) == req[j]) (dp[x][i | (1 << j)] += dp[x][i]) %= Mod;
}

class SimilarNames
{
	public:
		int count(vector <string> a, vector <int> info1, vector <int> info2)
		{
			m = SZ(info1);
			memset(req, 0, sizeof req);
			REP(i, 0, m) b[i] = mp(info1[i], info2[i]);
			sort(ALL(a), cmp);
			n = SZ(a);
			REP(i, 0, n)
			{
				fa[i] = n;
				REP(j, 0, i) if (is_prefix(a[j], a[i])) fa[i] = j;
			}
			memset(id, -1, sizeof id);
			REP(i, 0, m) id[b[i].x] = id[b[i].y] = 0;
			N = 0;
			REP(i, 0, n) if (~id[i]) id[i] = N++;
			REP(i, 0, m) b[i].x = id[b[i].x], b[i].y = id[b[i].y];
			memset(req, 0, sizeof req);
			memset(ban, 0, sizeof ban);
			REP(i, 0, m) req[b[i].x] |= 1 << b[i].y, ban[1 << b[i].x] |= 1 << b[i].y, ban[1 << b[i].y] |= 1 << b[i].x;
			REP(i, 0, 1 << N) REP(j, 0, N) if (i >> j & 1) ban[i] |= ban[1 << j];
			REP(i, 0, n + 1) adj[i].clear();
			REP(i, 0, n) adj[fa[i]].pb(i);
			S = (1 << N) - 1;
			memset(dp, 0, sizeof dp);
			dfs(n);
			int ret = dp[n][(1 << N) - 1];
			REP(i, 0, n - N) ret = (LL)ret * (i + 1) % Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
